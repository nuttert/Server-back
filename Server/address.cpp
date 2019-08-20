#include "address.hpp"
namespace socket
{
namespace address
{

Address::Address(const AddressStorage &addr, int type, int protocol)
    : Address(addr.GetDataAs(), type, protocol) {}

Address::Address(const void *addr, int type, int protocol)
    : type(type), protocol(protocol)
{
  auto *sockaddr = reinterpret_cast<const struct sockaddr *>(addr);
  domain = static_cast<AddressDomain>(sockaddr->sa_family);
  memory::Copy(storage.GetDataAs(), addr);
}

AddressDomain Address::Domain() const { return domain; }
native::sa_family_t Address::NativaDomain() const { return static_cast<native::sa_family_t>(domain); }
int Address::Type() const { return type; }
int Address::Protocol() const { return protocol; }

AddressStorage::AddressStorage(){
   utils::memory::SetToZero(native_data);
}

template <typename Type>
const Type &AddressStorage::GetDataAs() const
{
  return std::get<Type>(native_data);
}

template <typename Type>
Type &AddressStorage::GetDataAs()
{
  return std::get<Type>(native_data);
}

Length AddressStorage::Size() const
{
  return sizeof(native_data);
}

static constexpr socklen_t Addrlen(AddressDomain domain)
{
  switch (domain)
  {
  case AddressDomain::kInet:
    return sizeof(Inet);
  case AddressDomain::kInet6:
    return sizeof(Inet6);
  case AddressDomain::kUnix:
    return sizeof(Unix);
  case AddressDomain::kInvalid:;
    // fallthrough
  }
  throw std::logic_error("Unexpected address family " +
                         std::to_string(static_cast<int>(domain)));
}

} // namespace address
} // namespace socket
