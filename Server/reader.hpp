#pragma once
#include "socket.hpp"
#include <string>

namespace socket_space{
namespace reader{

struct Reader{
Reader(const Socket& socket);
std::string Read() const;
private:
const Socket& socket;
};

}
}
