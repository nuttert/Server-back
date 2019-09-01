#include "data_manager.hpp"
#include <Utils/Exceptions/file_exceptions.hpp>
namespace{
  namespace ex= exceptions;
}
namespace data{
    void DataManager::LoadConfigs(){
      configs_manager = std::make_shared<ConfigsManager>();
    }
    const DataManager::ConfigsManagerPtr DataManager::GetConfigs()const{
      if(!configs_manager)
        throw ex::NeedLoadError("You need to load configs before to use it!");
      return configs_manager;
    }
}
