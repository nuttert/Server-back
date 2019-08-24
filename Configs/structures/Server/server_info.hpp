#pragma once
#include "Configs/config_interface.hpp"

namespace yaml::configs
{


struct Server;

namespace ci = config_interface;

struct ServerInfo:ci::ConfigInfoInterface{
  using Structure = Server;
  const std::string GetGroup() const override;
  const std::string GetPath() const override;
  const std::string GetName() const override;
};


}
