#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "Engine/ECS/Types/ComponentID.h"

#include "../../Private/ECS/Types/Entity.h"
#include "../../Private/ECS/Types/TypesListOperations.h"
#include "../../Private/ECS/Types/Component.h"
#include "../../Private/Utils.h"

class World final
{

public:
    World() = default;
    ~World() = default;
    World(const World&) = delete;
    World(World&&) = delete;
    World& operator=(const World&) = delete;
    World& operator=(World&&) = delete;

    EntityId createEntity() noexcept;
    void destroyEntity(const EntityId entityId) noexcept;

//    template<typename T>
//    T& addComponent(const Entity e);
//
//    template<typename T>
//    T* getComponent(const Entity e);
//
    template<typename T>
    void removeComponent(const EntityId entityId) noexcept;

    template<typename ComponentsList>
    void registerComponents() noexcept;

private:
    std::vector<Entity> entities_;
    std::vector<ComponentsPool> components_;
};


template<typename T>
void World::removeComponent(const EntityId entityId) noexcept
{
    const auto entityIter {std::ranges::find_if(entities_,
        [entityId](const auto& elem) { return elem.getId() == entityId; })};
    if (!validateIter(entities_, entityIter))
    {
        return;
    }

    constexpr auto componentId{ T::getComponentId() };
    entityIter->removeComponent(componentId);

    const auto componentsIter { std::ranges::find_if(components_,
        [componentId](const auto& elem) { return elem.id == componentId; })};
    if (!validateIter(components_, componentsIter))
    {
        return;
    }

    componentsIter->components->removeComponent(entityId);
}

template<typename ComponentsList>
void World::registerComponents() noexcept
{
    if (components_.size() != 0)
    {
        return;
    }

    static_assert(ComponentsList::size > 0, "No components to register!");
    checkDuplicates<ComponentsList>();

    components_.reserve(ComponentsList::size);

    auto f{ [this] <typename... Ts>(TypesList<Ts...>)
    {
        ([this]
        {
            components_.emplace(
                ComponentsPool{.id = Ts::getComponentId(),
                .components = std::make_unique<Components<Ts>>()});
        }(), ...);
    } };

    f(ComponentsList{});
}
