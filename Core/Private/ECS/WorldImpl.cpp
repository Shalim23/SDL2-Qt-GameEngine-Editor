#include "WorldImpl.h"
#include <stdexcept>

namespace
{
    Entity nextEntity{0};
}

Entity WorldImpl::createEntity()
{
    if (freeEntities_.size() > 0)
    {
        auto emplaced{ entities_.emplace(freeEntities_.back(), std::unordered_map<size_t, size_t>{}) };
        freeEntities_.pop_back();
        return emplaced.first->first;
    }

    return entities_.emplace(++nextEntity, std::unordered_map<size_t, size_t>{}).first->first;
}

void WorldImpl::destroyEntity(const Entity e)
{
    const auto iter{entities_.find(e)};
    if (iter == entities_.end())
    {
        throw std::logic_error{"Trying to destroy non-existent entity!"};
    }

    for (const auto& [componentId, index] : iter->second)
    {
        //#TODO
        //remove component by index (removeComponentByIndex(const size_t index, const Entity e)
        //inside check if index is correct
    }

    freeEntities_.push_back(e);
    entities_.erase(e);
}

