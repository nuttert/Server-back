#include "reader_info.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

namespace yaml::configs
{

//Interface implementation______________________________________________________________________________
const std::string ReaderInfo::GetGroup() const
{
  static constexpr auto kGroup = "reader_group";
  return kGroup;
}
const std::string ReaderInfo::GetPath() const
{
  static constexpr auto kPath = "Configs/definitions/Reader/config.yaml";
  return kPath;
}
const std::string ReaderInfo::GetName() const
{
  static constexpr auto kName = "Reader";
  return kName;
}
//________________________________________________________________________________________

} // namespace yaml::configs
