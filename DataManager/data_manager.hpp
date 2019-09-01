#pragma once
#include <ServicesLists/ConfigsList.hpp>

namespace data{
struct DataManager{
 using ConfigsManager = yaml::configs::list::ConfigsManager;
 using ConfigsManagerPtr = std::shared_ptr<ConfigsManager>;
 DataManager() = default;
 void LoadConfigs();
 const ConfigsManagerPtr GetConfigs()const;
 private:
  ConfigsManagerPtr configs_manager;
};
}

