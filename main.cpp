#include <iostream>
#include <vector>
#include "Server/server.hpp"
#include <Configs/configs_manager.hpp>
#include <Configs/structures/Server/server.hpp>
#include <Configs/structures/Server/server_info.hpp>

std::string operator"" _s(const char *string, size_t size)
{
  std::string str;
  str.resize(size);
  str = string;
  return str;
}

int main()
{

  //  server::Server server(server::AddressType::kV4,8080);

  // server.Start();
  yaml::configs::ServerInfo server_info;
  yaml::configs::ConfigsManager configs(server_info);
  const auto structure = configs.GetStructure(server_info);
  std::cout << structure->GetIpv4();

  return 0;
}
