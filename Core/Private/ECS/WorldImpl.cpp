#include "WorldImpl.h"
#include <stdexcept>

namespace
{
    Entity nextEntity{0};
}

Entity WorldImpl::createEntity() noexcept
{
    if (freeEntities_.size() > 0)
    {
        auto emplaced{ entities_.emplace(freeEntities_.back(), std::vector<ComponentID>{}) };
        freeEntities_.pop_back();
        return emplaced.first->first;
    }

    return entities_.emplace(++nextEntity, std::vector<ComponentID>{}).first->first;
}

void WorldImpl::destroyEntity(const Entity e)
{
    const auto iter{entities_.find(e)};
    if (iter == entities_.end())
    {
        throw std::logic_error{"Trying to destroy non-existent entity!"};
    }

    for (const auto& componentId : iter->second)
    {
        auto iter{components_.find(componentId)};
        if (iter == components_.end())
        {
            throw std::logic_error{ "Unknown ComponentID!" };
        }
        iter->second->removeComponent(e);

        //#TODO
        //per-frame component removal
    }

    freeEntities_.push_back(e);
    entities_.erase(e);
}

size_t WorldImpl::getEntitiesAmount() const noexcept
{
    return entities_.size();
}
