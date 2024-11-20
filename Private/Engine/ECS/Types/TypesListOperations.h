#pragma once
#include <type_traits>
#include "Engine/ECS/Types/TypesList.h"

template<typename T>
struct IsTypesList : std::false_type {};

template<typename... Ts>
struct IsTypesList<TypesList<Ts...>> : std::true_type {};

//-

template<typename T, typename List>
struct ContainsType;

template<typename T>
struct ContainsType<T, TypesList<>> : std::false_type {};

template<typename T, typename... Ts>
struct ContainsType<T, TypesList<T, Ts...>> : std::true_type {};

template<typename T, typename U, typename... Ts>
struct ContainsType<T, TypesList<U, Ts...>> : ContainsType<T, TypesList<Ts...>> {};

//-

template<typename List>
struct FindDuplicate;

template<>
struct FindDuplicate<TypesList<>>
{
    using type = void;
};

template<typename T, typename... Ts>
struct FindDuplicate<TypesList<T, Ts...>>
{
    using type = typename std::conditional<
        ContainsType<T, TypesList<Ts...>>::value,
        T,
        typename FindDuplicate<TypesList<Ts...>>::type
    >::type;
};

//-

template <typename...>
struct DuplicatedType;

template<typename... Ts>
consteval void checkDuplicates() noexcept
{
    constexpr bool isDuplicate{ !std::is_void_v<typename FindDuplicate<Ts...>::type> };
    static_assert(!isDuplicate, "Type is already in the registry!");

    if constexpr (isDuplicate)
    {
        DuplicatedType<typename FindDuplicate<Ts...>::type>{};
    }
}

//-

template<typename List1, typename List2>
struct Concatenate;

template<typename... Ts1, typename... Ts2>
struct Concatenate<TypesList<Ts1...>, TypesList<Ts2...>>
{
    using type = TypesList<Ts1..., Ts2...>;
};
