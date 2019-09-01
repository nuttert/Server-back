#pragma once
#include <string>
#include <unordered_map>
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
  enum class ProcessorType{
    kMain
  };

private:
  using PropertiesNames = std::map<Properties, std::string>;
  using MapPoolTypeToSize = std::unordered_map<std::string, size_t>;
  using MapProcessorTypeToSting = std::map<ProcessorType, std::string>;
public:
  ThreadPool() = default;
  ThreadPool(const YAML::Node &node);

public:
  MapPoolTypeToSize type_to_size;
  static const PropertiesNames properties_names;
  static const MapProcessorTypeToSting processor_types_names;
};


} // namespace yaml::configs
