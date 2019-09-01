#include "reader.hpp"
#include <Utils/Exceptions/file_exceptions.hpp>
#include <iostream>

namespace
{
namespace ex = exceptions;
}
namespace yaml::configs
{

Reader::Reader(const YAML::Node &node)
{
  const auto &kAmountOfMillisecondsForReading = properties_names.at(Properties::kAmountOfMillisecondsForReading);
  try
  {
      milliseconds_for_reading = node[kAmountOfMillisecondsForReading].as<size_t>();
    
  }
  catch (const std::exception &except)
  {
    throw ex::KeyError(except.what());
  }
}

const Reader::PropertiesNames Reader::properties_names{
    {Properties::kAmountOfMillisecondsForReading, "milliseconds for reading"}};


} // namespace yaml::configs
