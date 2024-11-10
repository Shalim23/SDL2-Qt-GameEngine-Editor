#pragma once
#include <memory>
#include <vector>

#include "Engine/ECS/Types/ComponentId.h"
#include "Engine/ECS/Types/EntityId.h"

template<typename T>
struct Component
{
    EntityId entityId;
    T instance;
};

struct ComponentsBase
{
    virtual void removeComponent(const EntityId entityId) noexcept = 0;
};

template<typename T>
struct Components : ComponentsBase
{
    virtual void removeComponent(const EntityId entityId) noexcept override
    {
        auto iter{std::ranges::find_if(components_,
            [entityId](const auto& component){ return entityId == component.entityId; })};
        if (!validateIter(components_, iter))
        {
            return;
        }

        std::iter_swap(iter, std::prev(components_.end()));
        components_.pop_back();
    }
    
    std::vector<Component<T>> components_;
};

struct ComponentsPool
{
    ComponentId id;
    std::unique_ptr<ComponentsBase> components;
};
