#include "server.hpp"
#include <Utils/Exceptions/file_exceptions.hpp>

namespace
{
namespace ex = exceptions;
}
namespace yaml::configs
{

Server::Server(const YAML::Node &node)
{
  const auto& kName = properties_names.at(Properties::kName);
  const auto& kAddressType = properties_names.at(Properties::kAddressType);
  const auto& kAmountOfServiceThreads = properties_names.at(Properties::kAmountOfServiceThreads);
  const auto& kIpV6 = properties_names.at(Properties::kIpV6);
  const auto& kIpV4 = properties_names.at(Properties::kIpV4);
  const auto& kPort = properties_names.at(Properties::kPort);

  try{
  server_name = node[kName].as<std::string>();
  server_name = node[kAddressType].as<std::string>() == kIpV4 ? kIpV4 : kIpV6;
  amount_of_service_threads = node[kAmountOfServiceThreads].as<size_t>();
  port = node[kPort].as<size_t>();

  }catch(const std::exception& except){
    throw ex::KeyError(except.what());
  }
}



const Server::PropertiesNames Server::properties_names{
    {Properties::kName, "name"},
    {Properties::kAddressType, "address type"},
    {Properties::kAmountOfServiceThreads, "amount of service threads"},
    {Properties::kIpV6, "ipV6"},
    {Properties::kIpV4, "ipV4"},
    {Properties::kPort, "port"}};

} // namespace yaml::configs
