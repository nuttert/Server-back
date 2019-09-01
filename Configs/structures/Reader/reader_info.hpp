#pragma once
#include <Configs/config_interface.hpp>

namespace yaml::configs
{


struct Reader;

namespace ci = config_interface;

struct ReaderInfo:ci::ConfigInfoInterface{
  using Structure = Reader;
  const std::string GetGroup() const override;
  const std::string GetPath() const override;
  const std::string GetName() const override;
};


}
