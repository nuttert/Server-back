#pragma once
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <Utils/type_traits.hpp>
#include "types_container.hpp"

namespace
{
namespace mi = boost::multi_index;
namespace tt = utils::type_traits;
}
/*
Пример использования котейнера:
struct Struct
{
        std::string name;
        size_t number;

        struct ByName{};
        struct ByNumber{};

        using Tags = std::tuple<Struct::ByName, Struct::ByNumber>;____________required
        using PtrsToMembers = std::tuple<&Struct::name, &Struct::number>;________required
};

        MultiIndexContainer<Struct, std::tuple<Struct>> container{};

        container.emplace(MyStruct{"name", 123});
        container.emplace(MyStruct{"name_1", 123});

        const auto &list = container.get<MyStruct::ByName>();

        for (const auto &element : list)
        {
                std::cout << element.name << std::endl;
                std::cout << element.number << std::endl;
        }
*/

namespace utils
{
namespace containers
{
namespace
{

template <
    typename Structure,
    typename MemberType>
auto GetStructureOfPointer(MemberType Structure::*) -> Structure;

template <auto PtrToMember>
using StructureOfPointe = decltype(GetStructureOfPointer(PtrToMember));

template <
    typename Structure,
    typename MemberType>
auto GetMemberTypeOfPointer(MemberType (Structure::*)() const) -> MemberType;

template <
    typename Structure,
    typename MemberType>
auto GetMemberTypeOfPointer(MemberType Structure::*) -> MemberType;

template <auto PtrToMember>
using MemberTypeOfPointer = decltype(GetMemberTypeOfPointer(PtrToMember));

} // namespace

//________________________________________________________________________________
namespace
{
template <auto PtrToMember,
          typename Structure = StructureOfPointe<PtrToMember>,
          typename Type = MemberTypeOfPointer<PtrToMember>>
auto GetBoostMemberConstructor() -> mi::const_mem_fun<Structure, Type, PtrToMember>;

template <auto PtrToMember,
          typename Structure = StructureOfPointe<PtrToMember>,
          typename Type = MemberTypeOfPointer<PtrToMember>>
auto GetBoostMemberConstructor() -> mi::member<Structure, Type, PtrToMember>;

/*1.0 С помощью данного шаблона мы можем получить класс member, передав ему лишь указатель
на член структуры(класса)
        Structure - произвольная(ый) структура(класс)
        Type - тип члена
        PtrToMember - указатели на данный член
*/
template <auto PtrToMember>
using BoostMember = decltype(GetBoostMemberConstructor<PtrToMember>());

//1.1 С помощью данного шаблона мы можем получить класс tag
template <typename Tag>
using BoostTag = mi::tag<Tag>;
} // namespace
//________________________________________________________________________________
namespace
{
template <
    bool Unique = true,
    template <typename... Tags>
    typename TagsContainer,

    typename... Tags,

    template <auto... PtrsToMembers>
    typename PtrsToMembersContainer,

    auto... PtrsToMembers>
auto IndexConstructorForOneStructure(TagsContainer<Tags...>,
                                           PtrsToMembersContainer<PtrsToMembers...>)
{
    if constexpr (Unique)
        return std::tuple<mi::ordered_unique<BoostTag<Tags>, BoostMember<PtrsToMembers>>...>{};
    else
        return std::tuple<mi::ordered_non_unique<BoostTag<Tags>, BoostMember<PtrsToMembers>>...>{};
}


/*2. С помощью данного шаблона мы можем получить множество классов ordered_unique для одной структуры
        TagsContainer - совокупность тэгов
        Tags - сами тэги(пакет)

        PtrsToMembersContainer - контейнер указателей на методы
        PtrsToMembers - сами указатели
*/

template <typename Structure,
          typename Tags = typename Structure::Tags,
          typename PtrsToMembers = typename Structure::PtrsToMembers>
struct StructureUniqueProperies{
    using TagsContainer = Tags;
    using PtrsToMembersContainer = PtrsToMembers;
};

template <typename Structure>
struct StructureUniqueProperies<Structure,std::tuple<>,std::tuple<>>{};


template <typename Structure,
          typename TagsContainer = typename StructureUniqueProperies<Structure>::TagsContainer,
          typename PtrsToMembersContainer = typename StructureUniqueProperies<Structure>::PtrsToMembersContainer>
using IndexiesForOneStructure = decltype(IndexConstructorForOneStructure(TagsContainer{}, PtrsToMembersContainer{}));
} // namespace

//________________________________________________________________________________

namespace
{
template <
    template <typename... Structures>
    typename StructuresContainer,

    typename... Structures>
auto IndexConstructorForManyStructure(const StructuresContainer<Structures...> &)
    -> tt::TupleCat<IndexiesForOneStructure<Structures>...>;

/*4. С помощью данного шаблона мы можем получить множество классов ordered_unique для множества структур
        StructuresContainer - совокупность структур
        Structures - структуры(пакет типов)
*/
template <typename StructuresContainer>
using IndexiesForManyStructures = decltype(IndexConstructorForManyStructure(StructuresContainer{}));
} // namespace

//________________________________________________________________________________

namespace
{

template <
    template <typename... Indexies>
    typename IndexiesContainer,

    typename... Indexies>
auto IndexiesByConstructor(const IndexiesContainer<Indexies...> &)
    -> mi::indexed_by<Indexies...>;

/*5. С помощью данного шаблона мы можем получить множество классов index_by
        UniqueIndexiesContainer - совокупность индексов
*/
template <typename IndexiesContainer>
using IndexiesBy = decltype(IndexiesByConstructor(IndexiesContainer{}));
} // namespace
//________________________________________________________________________________

namespace
{

template <
    typename BaseStructure,

    template <typename... Structures>
    typename StructuresContainer,

    typename... Structures
    >
auto MultiIndexConstructorFromStructures
(BaseStructure, StructuresContainer<Structures...>)
    -> boost::multi_index_container<BaseStructure,
                                    IndexiesBy<
                                        IndexiesForManyStructures<
                                            StructuresContainer<Structures...>>>>;



} // namespace

/*5. С помощью данного шаблона мы можем получить класс boost::multi_index_container,
основываясь лишь на базовой структуре и её методах
*/
template <
    typename BaseStructure,
    typename DerivedStructure = BaseStructure,
    typename StructuresContainer = TypesContainer<DerivedStructure>>
using MultiIndexContainer = decltype(MultiIndexConstructorFromStructures(std::declval<BaseStructure>(), StructuresContainer{}));

} // namespace containers
} // namespace utils
