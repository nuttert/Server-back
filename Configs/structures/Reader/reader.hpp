#pragma once
#include <string>
#include <unordered_map>
#include <yaml-cpp/yaml.h>

namespace yaml::configs
{

class Reader
{
public:
  enum class Properties
  {
    kAmountOfMillisecondsForReading
  };

private:
  using PropertiesNames = std::map<Properties, std::string>;


public:
  Reader() = default;
  Reader(const YAML::Node &node);

public:
  size_t milliseconds_for_reading;
  static const PropertiesNames properties_names;

};


} // namespace yaml::configs
