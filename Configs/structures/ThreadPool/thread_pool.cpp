#include "thread_pool.hpp"
#include <Utils/Exceptions/file_exceptions.hpp>
#include <iostream>

namespace
{
namespace ex = exceptions;
}
namespace yaml::configs
{

ThreadPool::ThreadPool(const YAML::Node &node)
{
  const auto &kAmountOfThreads = properties_names.at(Properties::kAmountOfThreads);
  try
  {
    for(const auto& [kType, kTypeName]: processor_types_names){
      const auto current_type = node[kTypeName];
      type_to_size[kTypeName] = current_type[kAmountOfThreads].as<size_t>();
    }
  }
  catch (const std::exception &except)
  {
    throw ex::KeyError(except.what());
  }
}

const ThreadPool::PropertiesNames ThreadPool::properties_names{
    {Properties::kAmountOfThreads, "amount of threads"}};

  const ThreadPool::MapProcessorTypeToSting ThreadPool::processor_types_names{
    {ProcessorType::kMain,"main task processor"}
  };

} // namespace yaml::configs
