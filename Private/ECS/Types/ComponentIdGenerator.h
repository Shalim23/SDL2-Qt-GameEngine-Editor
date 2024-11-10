#pragma once
#include "Engine/ECS/Types/ComponentId.h"
#include <string_view>

consteval ComponentId generateComponentId(std::string_view str) noexcept
{
    std::uint64_t hash{ 14695981039346656037ull };
    for (char c : str)
    {
        hash ^= static_cast<std::uint64_t>(c);
        hash *= 1099511628211ull;
    }
    return hash;
}
