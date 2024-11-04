#pragma once

template<typename... Ts>
struct TypesList 
{
    static constexpr std::size_t size{sizeof...(Ts)};
};
