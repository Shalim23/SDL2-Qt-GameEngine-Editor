#pragma once

#include <memory>
#include <typeindex>
#include <vector>

#include "../../Private/Engine/ECS/Types/TypesListOperations.h"
#include "Types/SystemBase.h"

class World;

class SystemManager final
{
    struct System
    {
        std::type_index typeIndex;
        std::unique_ptr<SystemBase> system;
    };

public:
    SystemManager() = default;
    ~SystemManager() = default;
    SystemManager(const SystemManager&) = delete;
    SystemManager(SystemManager&&) = delete;
    SystemManager& operator=(const SystemManager&) = delete;
    SystemManager& operator=(SystemManager&&) = delete;

    void init(World&) noexcept;
    void update(World&) const noexcept;
    void shutdown() const noexcept;

    template<typename T>
    T* getSystem() noexcept;

    template<typename SystemsList>
    void registerSystems() noexcept;

private:
    std::vector<System> systems_;
};

template<typename T>
T* SystemManager::getSystem() noexcept
{
    auto iter{ std::ranges::find_if(systems_,
        [typeIndex = std::type_index{typeid(T)}](const System& s) { return s.typeIndex == typeIndex; }) };

    return iter != systems_.end() ? static_cast<T*>(iter->system.get()) : nullptr;
}

template<typename SystemsList>
void SystemManager::registerSystems() noexcept
{
    if (systems_.size() != 0)
    {
        return;
    }

    static_assert(SystemsList::size > 0, "No systems to register!");
    checkDuplicates<SystemsList>();

    systems_.reserve(SystemsList::size);

    auto f{ [this] <typename... Ts>(TypesList<Ts...>)
    {
        ([this]
        {
            auto& system{systems_.emplace_back(
                System{.typeIndex = std::type_index{ typeid(Ts)},
                       .system = std::make_unique<Ts>()}
                )};
        }(), ...);
    } };

    f(SystemsList{});
}
