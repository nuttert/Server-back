#include "server_utils.hpp"

namespace utils
{
size_t GetBufferLength(TCP::socket &socket)
{
  size_t length = 0;
  unsigned long get_buffer_size = FIONREAD;
  ioctl(socket.native_handle(), get_buffer_size, &length);
  return length;
}

} // namespace asio
