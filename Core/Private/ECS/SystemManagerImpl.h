#pragma once

#include <memory>
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <stdexcept>
#include <format>

#include "Types/TypesListOperations.h"
#include "Engine/ECS/Types/SystemBase.h"

class SystemManager;
class World;

class SystemManagerImpl final
{
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
    T& getSystem();

    template<typename SystemsList>
    void registerSystems();

private:
    std::vector<std::unique_ptr<SystemBase>> systems_;
    std::unordered_map<std::type_index, SystemBase*> systemById_;
};

template<typename T>
T& SystemManagerImpl::getSystem()
{
    const auto iter{ systemById_.find(std::type_index{typeid(T)}) };

    if (iter == systemById_.end())
    {
        throw std::logic_error{std::format("Cannot find system {}!", typeid(T).name())};
    }

    return *static_cast<T*>(iter->second);
}

template<typename SystemsList>
void SystemManagerImpl::registerSystems()
{
    if (systems_.size() != 0)
    {
        throw std::logic_error{"Systems are already initialized!"};
    }

    static_assert(SystemsList::size > 0, "No systems to register!");
    checkDuplicates<SystemsList>();

    systems_.reserve(SystemsList::size);

    auto f{ [this] <typename... Ts>(TypesList<Ts...>)
    {
        ([this]
        {
            auto& system{systems_.emplace_back(std::make_unique<Ts>())};
            systemById_.emplace(std::type_index{ typeid(Ts) }, system.get());
        }(), ...);
    } };

    f(SystemsList{});
}
