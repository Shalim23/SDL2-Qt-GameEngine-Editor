#pragma once

template<typename... Ts>
struct TypesList 
{
    static constexpr size_t size{sizeof...(Ts)};
};
