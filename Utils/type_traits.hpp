#pragma once
#include <type_traits>

namespace utils
{
namespace type_traits
{

namespace
{

template <bool arg, bool... args>
struct Conunctions
{
  static constexpr bool value = arg & Conunctions<args...>::value;
};

template <bool arg>
struct Conunctions<arg>
{
  static constexpr bool value = arg;
};

template <bool arg, bool... args>
struct Disunctions
{
  static constexpr bool value = arg | Disunctions<args...>::value;
};

template <bool arg>
struct Disunctions<arg>
{
  static constexpr bool value = arg;
};

template <
    template <typename...>
    typename Trait,
    typename One,
    typename... Other>
struct TraitOneOtherForConunctions
{
  static constexpr bool value = Conunctions<Trait<One, Other>::value...>::value;
};

template <
    template <typename...>
    typename Trait,
    typename One,
    typename... Other>
struct TraitOneOtherForDisunctions
{
  static constexpr bool value = Disunctions<Trait<One, Other>::value...>::value;
};

} // namespace

template <typename One, typename... Other>
struct is_same
{
  static constexpr bool value = TraitOneOtherForConunctions<std::is_same, One, Other...>::value;
};

template <typename One, typename... Other>
struct is_base_of
{
  static constexpr bool value = TraitOneOtherForConunctions<std::is_base_of, One, Other...>::value;
};

template <typename One, typename... Other>
struct is_one_of
{
  static constexpr bool value = TraitOneOtherForDisunctions<std::is_same, One, Other...>::value;
};

} // namespace type_traits
namespace type_traits
{
namespace
{
template <typename... T>
struct MakeVoid
{
  using Type = void;
};
template <typename... T>
using Void = typename MakeVoid<T...>::Type;
} // namespace

template <typename Structure, typename = void>
struct HasPropertyTags : std::false_type
{
};

template <typename Structure>
struct HasPropertyTags<Structure, Void<typename Structure::Tags>> : std::true_type
{
};

template <typename Structure, typename = void>
struct HasPropertyNonUniqueTags : std::false_type
{
};

template <typename Structure>
struct HasPropertyNonUniqueTags<Structure, Void<typename Structure::NonUniqueTags>> : std::true_type
{
};

template <typename Structure, typename = void>
struct HasPropertyPtrsToMembers : std::false_type
{
};

template <typename Structure>
struct HasPropertyPtrsToMembers<Structure, Void<typename Structure::PtrsToMembers>> : std::true_type
{
};

template <typename Structure, typename = void>
struct HasPropertyNonUniquePtrsToMembers : std::false_type
{
};

template <typename Structure>
struct HasPropertyNonUniquePtrsToMembers<Structure, Void<typename Structure::NonUniquePtrsToMembers>> : std::true_type
{
};

} // namespace type_traits

namespace type_traits
{
namespace
{
template <
    template <typename... Types>
    typename Container,

    typename... Types>
auto GetTupleFromContainer(Container<Types...>) -> std::tuple<Types...>;
}
template <typename Container>
using TupleFromContainer = decltype(GetTupleFromContainer(std::declval<Container>()));

template <typename... Containers>
using TupleCat = decltype(std::tuple_cat(std::declval<Containers>()...));

} // namespace type_traits

} // namespace utils
