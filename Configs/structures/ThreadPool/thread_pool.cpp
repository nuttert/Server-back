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
    amount_of_threads = node[kAmountOfThreads].as<size_t>();
  }
  catch (const std::exception &except)
  {
    throw ex::KeyError(except.what());
  }
}

const ThreadPool::PropertiesNames ThreadPool::properties_names{
    {Properties::kAmountOfThreads, "amount of threads"}};

} // namespace yaml::configs
