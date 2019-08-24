#include "server_info.hpp"

namespace yaml::configs
{

//Interface implementation______________________________________________________________________________
const std::string ServerInfo::GetGroup() const
{
  static constexpr auto kGroup = "server_group";
  return kGroup;
}
const std::string ServerInfo::GetPath() const
{
  static constexpr auto kPath = "Configs/definitions/Server/config.yaml";
  return kPath;
}
const std::string ServerInfo::GetName() const
{
  static constexpr auto kName = "Server";
  return kName;
}
//________________________________________________________________________________________

} // namespace yaml::configs
