#pragma once
#include "Configs/config_interface.hpp"

namespace yaml::configs
{


struct ThreadPool;

namespace ci = config_interface;

struct ThreadPoolInfo:ci::ConfigInfoInterface{
  using Structure = ThreadPool;
  const std::string GetGroup() const override;
  const std::string GetPath() const override;
  const std::string GetName() const override;
};


}
