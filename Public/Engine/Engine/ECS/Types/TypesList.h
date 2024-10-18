#pragma once

template<typename... Ts>
struct TypesList 
{
    constexpr std::size_t size{sizeof...(Ts)};
};
