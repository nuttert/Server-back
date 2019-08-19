#pragma once
#include <exception>
#include <string>

struct BaseException:std::exception{
  BaseException(const std::string& message):message{message}{}

  const char* what()const noexcept override{
    return message.c_str();
  }
  std::string message;
};


struct SocketOpenFailed:BaseException{
  using BaseException::BaseException;
};

struct SocketBindFailed:BaseException{
  using BaseException::BaseException;
};

struct SocketListenFailed:BaseException{
  using BaseException::BaseException;
};

struct SocketSelectFailed:BaseException{
  using BaseException::BaseException;
};

struct SocketNewClientFailed:BaseException{
  using BaseException::BaseException;
};


