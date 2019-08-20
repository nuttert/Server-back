
namespace utils{
namespace memory{

template<typename Type>
void SetToZero(Type& data);

template<typename From, typename To>
void Copy(const From& from,To& to);
}
}
#include "memory.cpp"
