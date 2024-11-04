#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "Types/ComponentsList.h"
#include "Engine/ECS/Types/Entity.h"

class World final
{

public:
    World() = default;
    ~World() = default;
    World(const World&) = delete;
    World(World&&) = delete;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = delete;

private:
    std::unordered_map<size_t, std::unique_ptr<ComponentsListBase>> components_;
    std::unordered_map<Entity, std::unordered_map<size_t, size_t>> entities_;
};