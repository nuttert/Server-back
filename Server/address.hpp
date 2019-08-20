#pragma once

#include <set>
#include <variant>
#include <string>
#include "memory.hpp"
#include "native_types.hpp"

namespace socket{
namespace address{

namespace native = native_types;

using AnyType = native::sockaddr;
using Inet = native::sockaddr_in;
using Inet6 = native::sockaddr_in6;
using Unix = native::sockaddr_un;
using Length = native::socklen_t;

enum class AddressDomain {
  kInvalid = -1,
  kInet = native::AF_INET,
  kInet6 = native::AF_INET6,
  kUnix = native::AF_UNIX
};

struct AddressStorage{

using Storage = std::variant<AnyType,
                             Inet,
                             Inet6,
                             Unix>;
public:
  AddressStorage();

  template<typename Type = AnyType>
  const Type& GetDataAs()const;

  template<typename Type = AnyType>
        Type& GetDataAs();

  Length Size() const;
  static constexpr Length Addrlen(AddressDomain domain);
private:
  size_t port;
  AddressDomain domain;
  Storage native_data;
};


struct Address{
  Address(const AddressStorage& addr, int type, int protocol);
  Address(const void* addr, int type, int protocol);

  AddressDomain Domain() const;
  native::sa_family_t NativaDomain() const;
  int Type() const;
  int Protocol() const;
private:
    AddressDomain domain{AddressDomain::kInvalid};
    int type{-1};
    int protocol{-1};
  AddressStorage storage;
};

}
}
