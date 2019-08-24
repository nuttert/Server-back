#include "literal_operators.hpp"

namespace utils::literal_operators
{
std::string operator"" _s(const char *string, size_t size)
{
  std::string str;
  str.resize(size);
  str = string;
  return str;
}
} // namespace utils::literal_operators
