#include "reader.hpp"
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/filio.h>
#include <vector>

namespace socket_space{
namespace reader{
Reader::Reader(const Socket& socket):socket(socket){}

std::string Reader::Read()const{
  size_t length = 0;
  unsigned long get_buffer_size = FIONREAD;
  ioctl(socket, get_buffer_size, &length);
  std::vector<char> buffer(length);
  read(socket, &buffer[0], length);
  std::string text{};
  text.assign(buffer.begin(),buffer.end());
  return text;
}

}
}
