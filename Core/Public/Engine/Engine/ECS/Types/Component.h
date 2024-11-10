#pragma once
#include <string_view>
#include "../../Private/ECS/Types/ComponentID.h"

consteval ComponentID generateComponentID(std::string_view str)
{
    std::uint64_t hash{14695981039346656037ull};
    for (char c : str)
    {
        hash ^= static_cast<std::uint64_t>(c);
        hash *= 1099511628211ull;
    }
    return hash;
}

#define COMPONENT_ID_GETTER(ComponentName) \
    static consteval ComponentID getComponentID() { return generateComponentID(#ComponentName); }
