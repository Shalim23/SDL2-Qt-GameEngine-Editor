#pragma once

#include <unordered_map>
#include <memory>
#include "Engine/ECS/Types/Entity.h"
#include "Types/ComponentID.h"
#include "Types/Components.h"
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
    size_t getEntitiesAmount() const noexcept;

    template<typename ComponentsList>
    void registerComponents();

private:
    std::unordered_map<Entity, std::vector<ComponentID>> entities_;
    std::vector<Entity> freeEntities_;
    std::unordered_map<ComponentID, std::unique_ptr<ComponentsBase>> components_;
};

template<typename ComponentsList>
void WorldImpl::registerComponents()
{
    if (components_.size() != 0)
    {
        throw std::logic_error{ "Components are already initialized!" };
    }

    static_assert(ComponentsList::size > 0, "No components to register!");
    checkDuplicates<ComponentsList>();

    components_.reserve(ComponentsList::size);

    auto f{ [this] <typename... Ts>(TypesList<Ts...>)
    {
        ([this]
        {
            components_.emplace(Ts::getComponentID(), std::make_unique<Components<Ts>>());
        }(), ...);
    } };

    f(ComponentsList{});
}
