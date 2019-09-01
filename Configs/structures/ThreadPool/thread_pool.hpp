#pragma once
#include <string>
#include <map>
#include <yaml-cpp/yaml.h>

namespace yaml::configs
{

class ThreadPool
{
public:
  enum class Properties
  {
    kAmountOfThreads
  };

private:
  using PropertiesNames = std::map<Properties, std::string>;

public:
  ThreadPool() = default;
  ThreadPool(const YAML::Node &node);

public:
  size_t amount_of_threads;
  static const PropertiesNames properties_names;
};

} // namespace yaml::configs
