#include "socket.hpp"
#include "exceptions.hpp"
#include <errno.h>
#include <iostream>

namespace socket_space{

const Socket::NativeConnectionType Socket::native_types{
{ConnectionType::kTCP, SOCK_STREAM},
{ConnectionType::kUDP, SOCK_DGRAM}
};

SetOfSockets::SetOfSockets(){
  clearSetOfSockets(fd_set_of_clients);
}

fd_set& SetOfSockets::GetNativeSet(){
  return fd_set_of_clients;
}

//Function for set of sockets//////////
void SetOfSockets::clearSetOfSockets(fd_set& set){FD_ZERO(&set);}
void SetOfSockets::removeSocketFromSet(int socket_descriptor,fd_set& set){FD_CLR(socket_descriptor, &set);}
void SetOfSockets::setSocket(int socket_descriptor,fd_set& set){FD_SET(socket_descriptor, &set);}
bool SetOfSockets::isSocketInSet(int socket_descriptor,const fd_set& set){return FD_ISSET(socket_descriptor, &set);}


void SetOfSockets::clearSetOfSockets(){clearSetOfSockets(fd_set_of_clients);}
void SetOfSockets::removeSocketFromSet(const Socket&  socket_descriptor){
  removeSocketFromSet(socket_descriptor, fd_set_of_clients);
  set_of_clients.erase(socket_descriptor);
}
void SetOfSockets::setSocket(const Socket&  socket_descriptor){
  setSocket(socket_descriptor, fd_set_of_clients);
  set_of_clients.emplace(socket_descriptor);
}
bool SetOfSockets::isSocketInSet(const Socket&  socket_descriptor)const{
  return isSocketInSet(socket_descriptor, fd_set_of_clients);
}


SetOfSockets::const_iterator SetOfSockets::begin()const{
  return set_of_clients.begin();
}

SetOfSockets::const_iterator SetOfSockets::end()const{
  return set_of_clients.end();
}

size_t SetOfSockets::size()const{
  return set_of_clients.size();
}




//1. socket creating
Socket::Socket(ConnectionType type){
    CreatSocket(type);
}

Socket::Socket(int descriptor,const Address& address):
socket_descriptor{descriptor},
address{address}{}


//1. socket creating
void Socket::CreatSocket(ConnectionType type){
     if((socket_descriptor = socket(AF_INET, native_types.at(type), 0)) < 0) 
      throw SocketOpenFailed{"Can't open socket"};
}

Socket::operator int()const{
  return socket_descriptor;
}

bool Socket::operator ==(const Socket& rhs){
  return socket_descriptor == rhs.socket_descriptor;
}
bool Socket::operator !=(const Socket& rhs){
  return !(*this == rhs);
}



void Socket::FullDestroy(){
      shutdown(socket_descriptor,DestroyType::kFull);
      close(socket_descriptor); 
}



//Listener


//2. Binding a socket to an address
void ListenerSocket::Binding(size_t port){
  memset(&address,0,sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  int option = 1;
  setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
  if(bind(socket_descriptor,(struct sockaddr*) &address, sizeof(address)) < 0)
    throw SocketBindFailed("Can't bind socket");
}

//3. Server is ready to accept requests
void ListenerSocket::Listen(size_t kMaximumClients){
    if(listen(socket_descriptor, kMaximumClients)<0)
      throw SocketListenFailed("Can't listen socket");
}



//5. Set a new client
AcceptedSocket ListenerSocket::AcceptNewClient(){
    Address new_client_address;
    memset(&new_client_address,0,sizeof(new_client_address));
    unsigned lenght_of_address = sizeof(new_client_address);
    memset(&new_client_address,0,lenght_of_address);
    int new_client = accept(socket_descriptor, (struct sockaddr*) &new_client_address,&lenght_of_address);
    if (new_client<0)
      throw SocketNewClientFailed("Can't accept new client");
    std::cout << "New connection accepted in fd: " << new_client << std::endl;
    return {new_client, std::move(new_client_address)};
}


SetOfSockets SetOfSockets::GetActiveSockets(const Socket& listener) const{
  const auto max_number_of_clients = std::max(size_t(listener), max_number_of_descriptors);
  Timer timeout;
  timeout.tv_sec = 1;
  timeout.tv_usec = 0;
  SetOfSockets active_clients{};
  auto fd_active_clients = fd_set_of_clients;
  int amountOfActiveClients = select(max_number_of_clients+1, &fd_active_clients, NULL, NULL,NULL);
  if (amountOfActiveClients < 0)
      throw SocketSelectFailed("Can't select sockets");
  for(const auto& socket:set_of_clients)
    if(isSocketInSet(socket, fd_active_clients))
      active_clients.setSocket(socket);
  return  active_clients;
}

}









