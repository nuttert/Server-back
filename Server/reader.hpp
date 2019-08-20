#pragma once
#include "socket.hpp"
#include <string>

namespace socket{
namespace reader{

struct Reader{
Reader(const Socket& socket);
std::string Read() const;
private:
const Socket& socket;
};

}
}
