#pragma once
#include <memory>
#include "socket.hpp"
#include "exceptions.hpp"

namespace server{

struct ServerImplementation;

struct Server{
public:
  Server() = default;
  Server(size_t port);
  void Start();
  void Stop();
private:
  std::unique_ptr<ServerImplementation> server;
  size_t port = 8080;
};


struct ServerImplementation{
private:
  using  Timer = timeval;
  using Address = sockaddr_in;
public:
ServerImplementation(size_t port = 8080);
  void start();
  void stop();
  void socketBinding();
  void serverIsGoingToListen();
  void weedOutPassiveClients();
  void setNewClient();
  void handleOldClients();
private:
  socket_space::ListenerSocket listener;
  size_t port;
  const size_t kMaximumClients{10};
  size_t max_file_descriptor{0};
  socket_space::SetOfSockets all_clients, active_clients;
  std::atomic_bool servise_is_ready{true};
};

}

