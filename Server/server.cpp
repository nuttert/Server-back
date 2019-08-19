#include "server.hpp"
#include <iostream>
#include "reader.hpp"
namespace server{

Server::Server(size_t port):port{port}{}

void Server::Start(){
  server = std::make_unique<ServerImplementation>(port);
  server->start();
}

void Server::Stop(){
  server->stop();
}


ServerImplementation::ServerImplementation(size_t port):port{port},listener{} {}
  void ServerImplementation::start(){
    socketBinding();
    serverIsGoingToListen();
    all_clients.setSocket(listener);
    while(servise_is_ready.load()){
      active_clients = all_clients;
      weedOutPassiveClients();
      if(active_clients.isSocketInSet(listener))
        setNewClient();
      handleOldClients();
    }
  }

  void ServerImplementation::stop(){
    servise_is_ready = false;
  }

 


//2. Binding a socket to an address
void ServerImplementation::socketBinding(){
    listener.Binding(port);
}


//3. Server is ready to accept requests
void ServerImplementation::serverIsGoingToListen(){
    listener.Listen(kMaximumClients);
}

//4. Select active clients
void ServerImplementation::weedOutPassiveClients(){
   active_clients = all_clients.GetActiveSockets(listener);
}

//5. Set a new client
void ServerImplementation::setNewClient(){
    auto new_client = listener.AcceptNewClient();
    all_clients.setSocket(new_client);
    active_clients.setSocket(new_client);
    if (new_client > max_file_descriptor) max_file_descriptor = new_client;
}


void ServerImplementation::handleOldClients(){
  for(auto client:active_clients){
    if(client == listener) continue;
    const auto reader = socket_space::reader::Reader(client);
    const auto text = reader.Read();
    std::cout<<text << std::endl;
    if(text.empty()){
      client.FullDestroy();
      all_clients.removeSocketFromSet(client);
      return;
    }
  }
}

}
