#pragma once
#include <memory>
#include <vector>

#include "Engine/ECS/Types/ComponentId.h"
#include "Engine/ECS/Types/EntityId.h"

template<typename T>
concept ComponentType = requires 
{
    { T::getComponentId() } -> std::same_as<ComponentId>;
};

template<typename T>
class Component
{
public:
    explicit Component(const EntityId entityId) noexcept
        : entityId_{entityId}
        , instance_{}
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
class Components : public ComponentsBase
{
public:
    virtual void removeComponent(const EntityId entityId) noexcept override
    {
        auto iter{std::ranges::find_if(components_,
            [entityId](const auto& component){ return entityId == component.getOwner(); })};
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

    std::vector<Component<T>>& getComponents() noexcept
    {
        return components_;
    }

    const std::vector<Component<T>>& getComponents() const noexcept
    {
        return components_;
    }

private:
    std::vector<Component<T>> components_;
};

struct ComponentsPool
{
    explicit ComponentsPool(const ComponentId id_, std::unique_ptr<ComponentsBase> components_)
        : id{ id_ }, components{ std::move(components_) }
    {}

    ComponentId id;
    std::unique_ptr<ComponentsBase> components;
};
