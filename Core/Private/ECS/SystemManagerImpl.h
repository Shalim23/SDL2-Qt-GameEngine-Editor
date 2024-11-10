#pragma once

#include <memory>
#include <typeindex>
#include <vector>

#include "Types/TypesListOperations.h"
#include "Engine/ECS/Types/SystemBase.h"

class SystemManager;
class World;

class SystemManagerImpl final
{
    struct System
    {
        std::type_index typeIndex;
        std::unique_ptr<SystemBase> system;
    };

public:
    SystemManagerImpl() = default;
    ~SystemManagerImpl() = default;
    SystemManagerImpl(const SystemManagerImpl&) = delete;
    SystemManagerImpl(SystemManagerImpl&&) = delete;
    SystemManagerImpl& operator=(const SystemManagerImpl&) = delete;
    SystemManagerImpl& operator=(SystemManagerImpl&&) = delete;

    void init(SystemManager&, World&) const noexcept;
    void update(World&) const noexcept;
    void shutdown() const noexcept;

    template<typename T>
    T* getSystem();

    template<typename SystemsList>
    void registerSystems();

private:
    std::vector<System> systems_;
};

template<typename T>
T* SystemManagerImpl::getSystem()
{
    auto iter{ std::ranges::find_if(systems_,
        [typeIndex = std::type_index{typeid(T)}](const System& s) { return s.typeIndex == typeIndex; }) };

    return iter != systems_.end() ? static_cast<T*>(iter->system.get()) : nullptr;
}

template<typename SystemsList>
void SystemManagerImpl::registerSystems()
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
