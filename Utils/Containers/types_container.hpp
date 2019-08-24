#pragma once
#include <array>
#include <utility>

namespace{

template <size_t Number>
struct Index
{};

}
namespace utils
{
namespace containers{
template <typename... Types>
struct TypesContainer
{
        static constexpr auto size = 0;
        constexpr static auto GetType(Index<size>) -> void;
};

template <typename Type, typename... Types>
struct TypesContainer<Type, Types...> : TypesContainer<Types...>
{
        static constexpr auto size = TypesContainer<Types...>::size + 1;
        using TypesContainer<Types...>::GetType;
        constexpr static auto GetType(Index<size>) -> Type;
};

template <typename Type>
struct TypesContainer<Type>
{
        static constexpr size_t size = 0;
        constexpr static auto GetType(Index<size>) -> Type;
};

template <typename Container, size_t Number>
using Type = decltype(Container::GetType(Index<Number>{}));


template<auto ...>
struct PtrContainer{};
} // namespace utils
}
