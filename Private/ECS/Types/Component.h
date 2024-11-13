#pragma once
#include <memory>
#include <vector>

#include "Engine/ECS/Types/ComponentId.h"
#include "Engine/ECS/Types/EntityId.h"

template<typename T>
concept ComponentType = requires { T::getComponentId(); };

template<typename T>
class Component
{
public:
    explicit Component(const EntityId entityId) noexcept
        : entityId_{entityId}
        , T{}
    {}

    EntityId getOwner() const noexcept
    {
        return entityId_;
    }

    T& getInstance() noexcept
    {
        return instance_;
    }

private:
    EntityId entityId_;
    T instance_;
};

class ComponentsBase
{
public:
    virtual void removeComponent(const EntityId entityId) noexcept = 0;
};

template<typename T>
class Components : ComponentsBase
{
public:
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

    T& addComponent(const EntityId entityId) noexcept
    {
        auto& newComponent{ components_.emplace_back(Component<T>{entityId}) };
        return newComponent.getInstance();
    }

private:
    std::vector<Component<T>> components_;
};

struct ComponentsPool
{
    ComponentId id;
    std::unique_ptr<ComponentsBase> components;
};
