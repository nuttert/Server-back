#pragma once
#include <string>

namespace utils::literal_operators
{
std::string operator "" _s (const char* string, size_t size);
}
