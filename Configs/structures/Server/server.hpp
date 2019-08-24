#pragma once
#include <string>
#include <map>
#include <yaml-cpp/yaml.h>

namespace yaml::configs
{

class Server
{
  enum class Properties;
  using PropertiesNames = std::map<Properties, std::string>;

private:
  enum class Properties
  {
    kName,
    kIpv4
  };

public:
  Server() = default;
  Server(const YAML::Node &node);

  const std::string GetIpv4() const;

private:
  std::string GetPropertyName(Properties property) const;

private:
  std::string server_name;
  std::string ipv4;
  size_t port;
  static const PropertiesNames properties_names;
};

} // namespace yaml::configs
