#pragma once
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/time.h>
#include <set>
#include <map>

namespace socket_space{

struct Socket{
public:
enum ConnectionType{kTCP,kUDP};
enum DestroyType{kFull = 2};
protected:
  using Address = sockaddr_in;
  using NativeConnectionType = std::map<ConnectionType, int>;
public:
  Socket(ConnectionType type = ConnectionType::kTCP);
  Socket(int descriptor, const Address& address);
  operator int()const;
  bool operator ==(const Socket& rhs);
  bool operator !=(const Socket& rhs);

  void FullDestroy();

private:
  void CreatSocket(ConnectionType type);
protected:
int socket_descriptor;
Address address;
protected:
static const NativeConnectionType native_types;
};



struct AcceptedSocket final: Socket{
  using Socket::Socket;
  
};


struct ListenerSocket final: Socket{
  using Socket::Socket;
  void Binding(size_t port);
  void Listen(size_t kMaximumClients);
  AcceptedSocket AcceptNewClient();
};




struct SetOfSockets{
using Set = std::set<Socket>;
using const_iterator = Set::const_iterator;
using  Timer = timeval;
public:
    SetOfSockets();
public:
//Function for set of sockets//////////
void clearSetOfSockets();
void removeSocketFromSet(const Socket& socket_descriptor);
void setSocket(const Socket&  socket_descriptor);
bool isSocketInSet(const Socket&  socket_descriptor)const;
fd_set& GetNativeSet();

SetOfSockets GetActiveSockets(const Socket& listener)const ;

const_iterator begin()const;
const_iterator end()const;

  size_t size()const;
private:
  //Function for set of sockets//////////
  static void clearSetOfSockets(fd_set& set);
  static void removeSocketFromSet(int socket_descriptor,fd_set& set);
  static void setSocket(int socket_descriptor,fd_set& set);
  static bool isSocketInSet(int socket_descriptor,const fd_set& set);
public:
    fd_set fd_set_of_clients;
    Set set_of_clients{};
    size_t max_number_of_descriptors{0};
};
}
