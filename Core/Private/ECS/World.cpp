#include "Engine/ECS/World.h"

Entity World::createEntity() noexcept
{
    return impl_.createEntity();
}

void World::destroyEntity(const Entity e)
{
    impl_.destroyEntity(e);
}

size_t World::getEntitiesAmount() const noexcept
{
    return impl_.getEntitiesAmount();
}
