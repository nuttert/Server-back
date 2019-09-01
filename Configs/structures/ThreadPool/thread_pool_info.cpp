#include "thread_pool_info.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

namespace yaml::configs
{

//Interface implementation______________________________________________________________________________
const std::string ThreadPoolInfo::GetGroup() const
{
  static constexpr auto kGroup = "thread_group";
  return kGroup;
}
const std::string ThreadPoolInfo::GetPath() const
{
  static constexpr auto kPath = "Configs/definitions/ThreadPool/config.yaml";
  return kPath;
}
const std::string ThreadPoolInfo::GetName() const
{
  static constexpr auto kName = "ThreadPool";
  return kName;
}
//________________________________________________________________________________________

} // namespace yaml::configs
