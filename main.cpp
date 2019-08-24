#include <iostream>
#include <vector>
#include "Server/server.hpp"





int main(){

 server::Server server(server::AddressType::kV4,8080);

server.Start();

  return 0;
}


