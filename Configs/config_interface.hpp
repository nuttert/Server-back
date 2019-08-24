#pragma once
#include <yaml-cpp/yaml.h>
#include <Tags/Tags.hpp>

namespace yaml::config_interface
{

class ConfigInfoInterface
{
  virtual const std::string GetName() const = 0;
  virtual const std::string GetGroup() const = 0;
  virtual const std::string GetPath() const = 0;
};

class ConfigManagerInterface
{
  using PtrToSelf = std::shared_ptr<ConfigManagerInterface>;

public:
  ConfigManagerInterface(const std::string &name, const std::string &group) : kName{name}, kGroup{group} {}

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
