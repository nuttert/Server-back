#pragma once
#include <string>
#include <map>
#include <yaml-cpp/yaml.h>

namespace yaml::configs
{

class Server
{
public:
  enum class Properties
  {
    kName,
    kPort,
    kAddressType,
    kAmountOfServiceThreadsForAccepting,
    kAmountOfServicesForWorking,
    kIpV6,
    kIpV4
  };
  enum class AddressType
  {
    kV4,
    kV6
  };

private:
  using PropertiesNames = std::map<Properties, std::string>;

public:
  Server() = default;
  Server(const YAML::Node &node);

public:
  std::string server_name;
  AddressType address_type;
  size_t port;
  size_t amount_of_service_threads_for_accepting;
  size_t amount_of_services_for_working;
  static const PropertiesNames properties_names;
};

} // namespace yaml::configs
