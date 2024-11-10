#pragma once

#include "../../Private/ECS/WorldImpl.h"

class World final
{

public:
    World() = default;
    ~World() = default;
    World(const World&) = delete;
    World(World&&) = delete;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = delete;

    Entity createEntity() noexcept;
    void destroyEntity(const Entity e);
    const std::unordered_map<Entity, std::vector<ComponentID>>& getEntities() const noexcept;

    template<typename ComponentsList>
    void registerComponents();

private:
    WorldImpl impl_;
};

template<typename ComponentsList>
void World::registerComponents()
{
    impl_.registerComponents<ComponentsList>();
}
