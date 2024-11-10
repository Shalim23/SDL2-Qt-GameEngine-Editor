#pragma once

#include <unordered_map>
#include <memory>
#include <algorithm>

#include "Engine/ECS/Types/Entity.h"
#include "Types/ComponentID.h"
#include "Types/Component.h"
#include "Types/TypesListOperations.h"

class WorldImpl final
{

public:
    WorldImpl() = default;
    ~WorldImpl() = default;
    WorldImpl(const WorldImpl&) = delete;
    WorldImpl(WorldImpl&&) = delete;
    WorldImpl& operator=(const WorldImpl&) = delete;
    WorldImpl& operator=(WorldImpl&&) = delete;

    Entity createEntity() noexcept;
    void destroyEntity(const Entity e);

    const std::unordered_map<Entity, std::vector<ComponentID>>& getEntities() const noexcept;

    template<typename T>
    T& addComponent(const Entity e);

    template<typename T>
    T* getComponent(const Entity e);

    template<typename T>
    void removeComponent(const Entity e);

    template<typename ComponentsList>
    void registerComponents();

private:
    void removeComponent(const ComponentID id, const Entity e);

    template<typename T>
    T* getComponent(const ComponentID id, const Entity e);

private:
    std::unordered_map<Entity, std::vector<ComponentID>> entities_;
    std::vector<Components> components_;
};

template<typename T>
T& WorldImpl::addComponent(const Entity e)
{
    const auto entityIter{ entities_.find(e) };
    if (entityIter == entities_.end())
    {
        throw std::logic_error{ "Trying to add component to non-existent entity!" };
    }

    constexpr auto componentID{ T::getComponentID() };

    auto& componentsID{ entityIter->second };
    const auto componentIter{ std::ranges::find(componentsID, componentID) };
    if (componentIter != componentsID.end())
    {
        throw std::logic_error{ "Entity already has component!" };
    }

    auto componentsIter{ components_.find(componentID) };
    if (componentsIter == components_.end())
    {
        throw std::logic_error{ "Unknown ComponentID!" };
    }

    auto& components{static_cast<Components<T>*>(componentsIter->second)};
    auto& newComponent{components.addComponent(e)};
    componentsID.push_back(componentID);
    return newComponent;
}

template<typename T>
T* WorldImpl::getComponent(const Entity e)
{
    const auto entityIter{ entities_.find(e) };
    if (entityIter == entities_.end())
    {
        throw std::logic_error{ "Trying to get component from non-existent entity!" };
    }

    constexpr auto componentID{ T::getComponentID() };

    auto& componentsID{ entityIter->second };
    const auto componentIter{ std::ranges::find(componentsID, componentID) };
    if (componentIter == componentsID.end())
    {
        return nullptr;
    }

    return getComponent<T>(componentsID, e);
}

template<typename T>
T* WorldImpl::getComponent(const ComponentID id, const Entity e)
{
    auto componentsIter{ components_.find(id) };
    if (componentsIter == components_.end())
    {
        throw std::logic_error{ "Unknown ComponentID!" };
    }

    auto& components{ static_cast<Components<T>*>(componentsIter->second) };
    return components.getComponent(e);
}

template<typename T>
void WorldImpl::removeComponent(const Entity e)
{
    const auto iter{ entities_.find(e) };
    if (iter == entities_.end())
    {
        throw std::logic_error{ "Trying to remove component from non-existent entity!" };
    }

    auto& componentsID{ iter->second };
    auto componentIter{ std::ranges::find(componentsID, T::getComponentID())};
    if (componentIter == componentsID.end())
    {
        throw std::logic_error{ "Cannot find component!" };
    }

    removeComponent(*componentIter, e);

    const auto componentIndex{std::distance(componentsID.begin(), componentIter)};
    if (componentIndex == componentsID.size() - 1)
    {
        componentsID.pop_back();
        return;
    }

    std::iter_swap(componentIter, std::prev(componentsID.end()));
    componentsID.pop_back();
}

template<typename ComponentsList>
void WorldImpl::registerComponents()
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
                Components{.id = Ts::getComponentID(),
                .components = std::make_unique<Components<Ts>>()});
        }(), ...);
    } };

    f(ComponentsList{});
}
