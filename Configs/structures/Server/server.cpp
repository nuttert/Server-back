#include "server.hpp"

namespace yaml::configs
{

Server::Server(const YAML::Node &node)
{
  const auto kName = GetPropertyName(Properties::kName);
  const auto kIpv4 = GetPropertyName(Properties::kIpv4);

  server_name = node[kName].as<std::string>();
  ipv4 = node[kIpv4].as<std::string>();
}

std::string Server::GetPropertyName(Properties property) const
{
  return properties_names.at(property);
}

const std::string Server::GetIpv4() const
{
  return ipv4;
}

const Server::PropertiesNames Server::properties_names{
    {Properties::kName, "name"},
    {Properties::kIpv4, "ipv4"}};

} // namespace yaml::configs
