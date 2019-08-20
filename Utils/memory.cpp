#ifndef MEMORY_CPP
#define MEMORY_CPP
#include <string.h>
#include "memory.hpp"

namespace utils{
namespace memory{

template<typename Type>
void SetToZero(Type& data){
 ::memset(&data, 0 ,sizeof(data));
}

template<typename From, typename To>
void Copy(const From& from,To& to){
  static_assert(sizeof(to) < sizeof(from));
  ::memcpy(&to, &from, sizeof(from));
}

}
}
#endif
