#ifndef CONFIGS_MANAGER_TPP
#define CONFIGS_MANAGER_TPP
#include <iostream>
#include "configs_manager.hpp"
#include <Utils/type_traits.hpp>
#include <boost/asio.hpp>
#include <Utils/Exceptions/file_exceptions.hpp>

namespace
{
namespace ex = exceptions;
}

namespace yaml::configs
{

template <typename DocumentInfo>
ConfigManager<DocumentInfo>::ConfigManager(const DocumentInfo &document_info)
    : ConfigManagerInterface{document_info.GetName(), document_info.GetGroup()}
{
  try
  {
    root = YAML::LoadFile(document_info.GetPath());
  }
  catch (const std::exception &except)
  {
    throw ex::LoadFileError(document_info.GetPath());
  }
  document_ = std::make_unique<Document>(root[kName]);
}

template <typename DocumentInfo>
const typename ConfigManager<DocumentInfo>::DocumentPtr
ConfigManager<DocumentInfo>::GetStructure() const
{
  return document_;
}

template <typename... DocumentsInfo>
ConfigsManager<DocumentsInfo...>::ConfigsManager(const DocumentsInfo &... documents_info)
{
  namespace tt = utils::type_traits;
  static_assert(tt::is_base_of<ci::ConfigInfoInterface, DocumentsInfo...>::value, "Not approptiate type!");

  configs_managers.emplace(std::make_shared<
                           ConfigManager<DocumentsInfo>>(documents_info)...);
}

template <typename... DocumentsInfo>
template <typename DocumentInfo,
          typename Document>
const std::shared_ptr<Document> ConfigsManager<DocumentsInfo...>::GetStructure(const DocumentInfo &document_info) const
{
  namespace tt = utils::type_traits;
  static_assert(tt::is_one_of<DocumentInfo, DocumentsInfo...>::value, "Not approptiate type!");

  using ConfigForTheDocInfo = ConfigManager<DocumentInfo>;
  typename ConfigForTheDocInfo::DocumentPtr document_;

  const auto &list_of_configs_managers_for_directory = configs_managers.get<container::tags::ByName>();
  const auto configs_managers_iterator = list_of_configs_managers_for_directory.find(document_info.GetName());
  const auto end = list_of_configs_managers_for_directory.end();

  if (configs_managers_iterator != end)
  {
    auto &config_interface = *configs_managers_iterator;
    auto config = std::dynamic_pointer_cast<const ConfigForTheDocInfo>(config_interface);
    if (!config)
      throw std::runtime_error("Config doesn't exist!");
    document_ = config->GetStructure();
  }
  return document_;
}

} // namespace yaml::configs

#endif
