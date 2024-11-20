#include "Engine/ECS/World.h"

namespace
{
    EntityId nextEntityId{ 0 };
}

EntityId World::createEntity() noexcept
{
    //#TODO reuse entities
    return entities_.emplace_back(++nextEntityId).getId();
}

void World::destroyEntity(const EntityId entityId) noexcept
{
    const auto iter{std::ranges::find_if(entities_,
        [entityId](const auto& elem){ return elem.getId() == entityId; })};
    if (!validateIter(entities_, iter))
    {
        return;
    }

    //#TODO per-frame remove
    for (const auto componentId : iter->getComponents())
    {
        //#TODO remove components
    }

    std::iter_swap(iter, std::prev(entities_.end()));
    entities_.pop_back();
}
