#pragma once
#include <vector>
#include "Engine/ECS/Types/EntityId.h"
#include "Engine/ECS/Types/ComponentId.h"
#include "../../Utils.h"

class Entity
{
public:
    explicit Entity(const EntityId id)
        : id_{id}, components_{}
    {}

    ~Entity() = default;
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    Entity(Entity&& other) noexcept
        : id_{ other.id_ }, components_{ std::move(other.components_) }
    {}

    Entity& operator=(Entity&& other) noexcept 
    {
        if (this != &other)
        {
            id_ = other.id_;
            components_ = std::move(other.components_);
        }
        return *this;
    }

    EntityId getId() const noexcept
    {
        return id_;
    }

    const std::vector<ComponentId>& getComponents() const noexcept
    {
        return components_;
    }

    void removeComponent(const ComponentId id) noexcept
    {
        const auto iter {std::ranges::find(components_, id)};
        if (!validateIter(components_, iter))
        {
            return;
        }

        std::iter_swap(iter, std::prev(components_.end()));
        components_.pop_back();
    }

    bool hasComponent(const ComponentId id) const noexcept
    {
        return std::ranges::find(components_, id) != components_.end();
    }

    void addComponent(const ComponentId id) noexcept
    {
        components_.push_back(id);
    }

private:

    EntityId id_;
    std::vector<ComponentId> components_;
};
