#pragma once

#include <unordered_map>
#include "Engine/ECS/Types/Entity.h"

class WorldImpl final
{

public:
    WorldImpl() = default;
    ~WorldImpl() = default;
    WorldImpl(const WorldImpl&) = delete;
    WorldImpl(WorldImpl&&) = delete;
    WorldImpl& operator=(const WorldImpl&) = delete;
    WorldImpl& operator=(WorldImpl&&) = delete;

    Entity createEntity();
    void destroyEntity(const Entity e);

private:
    std::unordered_map<Entity, std::unordered_map<size_t, size_t>> entities_;
    std::vector<Entity> freeEntities_;
    //std::unordered_map<size_t, std::unique_ptr<ComponentsListBase>> components_;
};