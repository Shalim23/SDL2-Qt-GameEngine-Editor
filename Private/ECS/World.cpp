#include "Engine/ECS/World.h"

Entity World::createEntity() noexcept
{
    return impl_.createEntity();
}

void World::destroyEntity(const Entity e)
{
    impl_.destroyEntity(e);
}

const std::unordered_map<Entity, std::vector<ComponentID>>& World::getEntities() const noexcept
{
    return impl_.getEntities();
}
