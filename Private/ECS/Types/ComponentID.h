#pragma once
#include <cstdint>
#include <string_view>

using ComponentID = uint64_t;

consteval ComponentID generateComponentID(std::string_view str)
{
    std::uint64_t hash{ 14695981039346656037ull };
    for (char c : str)
    {
        hash ^= static_cast<std::uint64_t>(c);
        hash *= 1099511628211ull;
    }
    return hash;
}
