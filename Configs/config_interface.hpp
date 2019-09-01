#pragma once
#include <yaml-cpp/yaml.h>
#include <ServicesLists/TagsList.hpp>

namespace yaml::config_interface
{

class ConfigInfoInterface
{
  using Structure = void;
  virtual const std::string GetName() const = 0;
  virtual const std::string GetGroup() const = 0;
  virtual const std::string GetPath() const = 0;
};

class ConfigManagerInterface
{
  using PtrToSelf = std::shared_ptr<ConfigManagerInterface>;

public:
  template <
  typename DocumentInfo,
  class = std::enable_if_t<std::is_base_of<ConfigInfoInterface, DocumentInfo>::value>>
  ConfigManagerInterface(const DocumentInfo &ducument_info):kName{ducument_info.GetName()},kGroup{ducument_info.GetGroup()}
  {
    static_assert(std::is_base_of<ConfigInfoInterface, DocumentInfo>::value, "Not approptiate type!");
  }

  virtual const std::string GetName() const { return kName; };
  virtual const std::string GetGroup() const { return kGroup; };

  using Tags = configs::container::tags::Tags;
  using PtrsToMembers = utils::containers::PtrContainer<&ConfigManagerInterface::GetName,
                                                        &ConfigManagerInterface::GetGroup,
                                                        &PtrToSelf::get>;

protected:
  const std::string kName;
  const std::string kGroup;
};

} // namespace yaml::config_interface
