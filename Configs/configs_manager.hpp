#pragma once
#include "config_interface.hpp"
#include <Utils/Containers/multi_index_container.hpp>

namespace yaml::configs
{

namespace ci = config_interface;

template <typename DocumentInfo>
class ConfigManager : public ci::ConfigManagerInterface
{
public:
  using Document = typename DocumentInfo::Structure;
  using DocumentPtr = std::shared_ptr<Document>;

public:
  ConfigManager(const DocumentInfo &document_info);

  const DocumentPtr GetStructure() const;

private:
  DocumentPtr document_;
  YAML::Node root;
};

template <typename... DocumentsInfo>
class ConfigsManager
{
  using ConfigManagerInterfacePtr = std::shared_ptr<ci::ConfigManagerInterface>;
  using Container = utils::containers::MultiIndexContainer<ConfigManagerInterfacePtr, ci::ConfigManagerInterface>;
  using ContainerPtr = std::unique_ptr<Container>;

public:
  ConfigsManager(const DocumentsInfo &... documents_info);

  template <typename DocumentInfo,
            typename Document = typename DocumentInfo::Structure>
  const std::shared_ptr<Document> GetStructure(const DocumentInfo &document_info) const;

private:
  Container configs_managers{};
};

} // namespace yaml::configs

#include "configs_manager.tpp"
