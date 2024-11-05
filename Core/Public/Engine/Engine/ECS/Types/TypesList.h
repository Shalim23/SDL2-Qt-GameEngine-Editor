#pragma once

template<typename... Ts>
struct TypesList 
{
    static constexpr size_t size{sizeof...(Ts)};

    static consteval size_t getLargestTypeSize()
        { return (std::max({sizeof(Ts)...})); }
};
