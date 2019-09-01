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

struct NeedLoadError : public std::exception
{
  NeedLoadError(const std::string &message) : message(message) {}
  const char *what() const noexcept override
  {
    return message.c_str();
  }
  const std::string message{};
};

struct KeyError: public std::exception{
  KeyError(const std::string& message):message(message){}
 const char* what() const noexcept override {
   return message.c_str();
  }
  const std::string message{};
};

struct BadConfig: public std::exception{
  BadConfig(const std::string& message):message(message){}
 const char* what() const noexcept override {
   return message.c_str();
  }
  const std::string message{};
};

struct CannotFindConfig: public std::exception{
  CannotFindConfig(const std::string& message):message(message){}
 const char* what() const noexcept override {
   return message.c_str();
  }
  const std::string message{};
};
struct CannotConstructConfig: public std::exception{
  CannotConstructConfig(const std::string& message):message(message){}
 const char* what() const noexcept override {
   return message.c_str();
  }
  const std::string message{};
};
} // namespace exceptions

