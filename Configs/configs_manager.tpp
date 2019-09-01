#ifndef CONFIGS_MANAGER_TPP
#define CONFIGS_MANAGER_TPP
#include <iostream>
#include "configs_manager.hpp"
#include <boost/asio.hpp>
#include <Utils/type_traits.hpp>
#include <Utils/Exceptions/file_exceptions.hpp>
#include <boost/filesystem.hpp>
namespace
{
namespace ex = exceptions;
}

namespace yaml::configs
{

/*
Get document name and path
calls LoafFile()
@throw LoadFileError */
template <typename DocumentInfo>
ConfigManager<DocumentInfo>::ConfigManager():ci::ConfigManagerInterface(DocumentInfo{})
{
  static_assert(std::is_default_constructible<DocumentInfo>::value, "No default constuctor!");
  LoadFile();
}

/*
Load/reload file from path
@throw LoadFileError */
template <typename DocumentInfo>
void ConfigManager<DocumentInfo>::LoadFile(){
  const auto document_info = DocumentInfo{};
  try
  {
  
    root = YAML::LoadFile(document_info.GetPath());
    std::cout << "LOAD CONFIG: " << document_info.GetName();
  }
  catch (const std::exception &except)
  {
    throw ex::LoadFileError(document_info.GetPath()+ " " + except.what());
  }
  document_ = std::make_unique<Document>(root[kName]);
}

/*
GetDocument structure*/
template <typename DocumentInfo>
const typename ConfigManager<DocumentInfo>::DocumentPtr
ConfigManager<DocumentInfo>::GetStructure() const noexcept
{
  return document_;
}

/*
Loads yamls to structures from the documents info paths*/
template <typename... DocumentsInfo>
ConfigsManager<DocumentsInfo...>::ConfigsManager()
{
  namespace tt = utils::type_traits;
  static_assert(tt::is_base_of<ci::ConfigInfoInterface, DocumentsInfo...>::value, "Not appropriate type!");
  static_assert((std::is_default_constructible<DocumentsInfo>::value & ...), "No default constructor!");


  bool configs_constructed = (configs_managers.emplace(std::make_shared<
                           ConfigManager<DocumentsInfo>>()).second &...);
  if(!configs_constructed)
  throw ex::CannotConstructConfig{"Can't construct config"};
}

/*
@throw runtime_error - Cannot cast config interface
GetDocument structure*/
template <typename... DocumentsInfo>
template <typename DocumentInfo,
          typename Document>
const std::shared_ptr<Document> ConfigsManager<DocumentsInfo...>::GetStructure() const
{
  namespace tt = utils::type_traits;
  static_assert(tt::is_one_of<DocumentInfo, DocumentsInfo...>::value, "Not approptiate type!");

  using ConfigForTheDocInfo = ConfigManager<DocumentInfo>;
  using DocumentPtr= typename ConfigForTheDocInfo::DocumentPtr;
  DocumentPtr document_{};
  const auto document_info = DocumentInfo{};

  const auto &list_of_configs_managers_for_directory = configs_managers.get<container::tags::ByName>();
  const auto configs_managers_iterator = list_of_configs_managers_for_directory.find(document_info.GetName());
  const auto end = list_of_configs_managers_for_directory.end();

  if (configs_managers_iterator != end)
  {
    auto &config_interface = *configs_managers_iterator;
    auto config = std::dynamic_pointer_cast<const ConfigForTheDocInfo>(config_interface);
    if (!config)
      throw std::runtime_error("Cannot cast config interface to config!");
    document_ = config->GetStructure();
  }else{
    throw ex::CannotFindConfig("Can't find config: " + document_info.GetName());
  }
  return document_;
}

} // namespace yaml::configs

#endif
