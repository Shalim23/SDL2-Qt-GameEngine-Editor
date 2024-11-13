#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <format>

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

    template<ComponentType T>
    T& addComponent(const EntityId entityId);

    template<ComponentType T>
    T* getComponent(const EntityId entityId) noexcept;

    template<ComponentType T>
    void removeComponent(const EntityId entityId) noexcept;

    template<typename ComponentsList>
    void registerComponents() noexcept;

private:
    template<ComponentType T>
    T* getComponent(const EntityId entityId, const ComponentId componentId) noexcept;

    template<typename T>
    std::vector<Component<T>>& getComponents(ComponentsBase* components) noexcept
    {
        return *static_cast<Components<T>*>(components)->components;
    }

private:
    std::vector<Entity> entities_;
    std::vector<ComponentsPool> components_;
};


template<ComponentType T>
T& World::addComponent(const EntityId entityId)
{
    const auto entityIter{ std::ranges::find_if(entities_,
                [entityId](const auto& elem) { return elem.getId() == entityId; }) };
    if (!validateIter(entities_, entityIter))
    {
        throw std::logic_error{std::format("Entity {} doesn't exist!", entityId)};
    }

    constexpr auto componentId{ T::getComponentId() };
    if (entityIter->hasComponent(componentId))
    {
        assert(!"Trying to add existing component!");
        return *getComponent<T>(entityId, componentId);
    }

    const auto componentsPoolIter{ std::ranges::find_if(components_,
            [componentId](const auto& elem) { return elem.id == componentId; }) };
    if (!validateIter(components_, componentsPoolIter))
    {
        throw std::logic_error{ std::format("Component {} doesn't exist!", componentId) };
    }

    auto& components{ getComponents(componentsPoolIter->components.get()) };
    auto& newComponent{components.addComponent(entityId)};

    entityIter->addComponent(componentId);
    return newComponent;
}

template<ComponentType T>
T* World::getComponent(const EntityId entityId) noexcept
{
    const auto entityIter{ std::ranges::find_if(entities_,
            [entityId](const auto& elem) { return elem.getId() == entityId; }) };
    if (!validateIter(entities_, entityIter))
    {
        return nullptr;
    }

    constexpr auto componentId{ T::getComponentId() };
    if (!entityIter->hasComponent(componentId))
    {
        return nullptr;
    }

    return getComponent<T>(entityId, componentId);
}

template<ComponentType T>
T* World::getComponent(const EntityId entityId, const ComponentId componentId) noexcept
{
    const auto componentsPoolIter{ std::ranges::find_if(components_,
            [componentId](const auto& elem) { return elem.id == componentId; }) };
    if (!validateIter(components_, componentsPoolIter))
    {
        return nullptr;
    }

    auto& components{ getComponents(componentsPoolIter->components.get()) };
    const auto componentIter{ std::ranges::find_if(components,
        [entityId](const auto& elem) { return elem.entityId == entityId; }) };
    if (!validateIter(components, componentIter))
    {
        return nullptr;
    }

    return &componentIter->instance;
}

template<ComponentType T>
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
            static_assert(std::is_invocable_v<decltype(&Ts::getComponentId)>,
                          "Component must have COMPONENT_ID_GETTER");

            components_.emplace(
                ComponentsPool{.id = Ts::getComponentId(),
                .components = std::make_unique<Components<Ts>>()});
        }(), ...);
    } };

    f(ComponentsList{});
}
