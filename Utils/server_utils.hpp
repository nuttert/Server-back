#pragma once
#include <boost/asio.hpp>

namespace utils
{

namespace asio = boost::asio;
namespace ip = asio::ip;

using TCP = ip::tcp;

size_t GetBufferLength(TCP::socket &socket);
} // namespace asio


