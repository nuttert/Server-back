#include <iostream>
#include <vector>
#include <unordered_map>
#include <atomic>
#include <thread>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <exception>
#include "Configs/configs.hpp"
#include "Server/server.hpp"



int main(){
  // using Server = yaml::configs::Server;
  // auto config = yaml::configs::Config<Server>("Configs/config.yaml");
  // const auto server = config.GetServer();
  // std::cout << server.GetName() << server.GetIpv4();
  server::Server server{};
  server.Start();
  return 0;
}


