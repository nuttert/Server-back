#pragma once
#include <exception>
#include <string>

namespace exceptions
{
struct LoadFileError : public std::exception
{
  LoadFileError(const std::string &message) : message(message) {}
  const char *what() const noexcept override
  {
    return message.c_str();
  }
  const std::string message{};
};
} // namespace exceptions
// struct LoadFileError: public std::exception{
//   LoadFileError(const std::string& message):message(message){}
//  const char* what() const noexcept override {
//    return message.c_str();
//   }
//   const std::string message{};
// };
