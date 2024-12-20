#pragma once

#include <vector>
#include <span>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <format>

#include "Engine/ECS/Types/ComponentID.h"

#include "../../Private/Engine/ECS/Types/Entity.h"
#include "../../Private/Engine/ECS/Types/TypesListOperations.h"
#include "../../Private/Engine/ECS/Types/Component.h"
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

    template<ComponentType T>
    std::span<EntityId> getEntitiesWithComponent() const noexcept;

    template<typename ComponentsList>
    void registerComponents() noexcept;

private:
    template<ComponentType T>
    T* getComponent(const EntityId entityId, const ComponentId componentId) noexcept;

    template<typename T>
    Components<T>& getComponents(ComponentsBase* components) noexcept
    {
        return *static_cast<Components<T>*>(components);
    }

    template<typename T>
    const Components<T>& getComponents(ComponentsBase* components) const noexcept
    {
        return *static_cast<const Components<T>*>(components);
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
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_FUNCTION,
            std::format("Entity {} doesn't exist!", entityId).c_str(), nullptr);
        throw std::logic_error{std::format("Entity {} doesn't exist!", entityId)};
    }

    constexpr auto componentId{ T::getComponentId() };
    if (entityIter->hasComponent(componentId))
    {
        SDL_assert(!"Trying to add existing component!");
        return *getComponent<T>(entityId, componentId);
    }

    const auto componentsPoolIter{ std::ranges::find_if(components_,
            [componentId](const auto& elem) { return elem.id == componentId; }) };
    if (!validateIter(components_, componentsPoolIter))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_FUNCTION,
            std::format("Component {} doesn't exist!", componentId).c_str(), nullptr);
        throw std::logic_error{ std::format("Component {} doesn't exist!", componentId) };
    }

    auto& components{ getComponents<T>(componentsPoolIter->components.get()) };
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

    auto& components{ getComponents<T>(componentsPoolIter->components.get()).getComponents()};
    auto componentIter{ std::ranges::find_if(components,
        [entityId](const auto& elem) { return elem.getOwner() == entityId; })};
    if (!validateIter(components, componentIter))
    {
        return nullptr;
    }

    return &componentIter->getInstance();
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

template<ComponentType T>
std::span<EntityId> World::getEntitiesWithComponent() const noexcept
{
    constexpr auto componentId{ T::getComponentId() };

    const auto componentsPoolIter{ std::ranges::find_if(components_,
            [componentId](const auto& elem) { return elem.id == componentId; }) };
    if (!validateIter(components_, componentsPoolIter))
    {
        return {};
    }

    const auto& components{getComponents<T>(componentsPoolIter->components.get()).getComponents()};

    thread_local std::vector<EntityId> entities;
    entities.clear();
    entities.reserve(components.size());

    std::transform(components.begin(), components.end(), std::back_inserter(entities),
        [](const auto& component) { return component.getOwner(); });

    return std::span<EntityId>{entities};
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
            static_assert(ComponentType<Ts>, "Component must have COMPONENT_ID_GETTER");

            components_.emplace_back(Ts::getComponentId(), std::make_unique<Components<Ts>>());
        }(), ...);
    } };

    f(ComponentsList{});
}
