#pragma once

#include <memory>
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <stdexcept>
#include <format>

#include "Types/TypesListOperations.h"

class SystemManager;
class World;

class SystemManagerImpl final
{
public:
    SystemManagerImpl() = default;
    ~SystemManagerImpl() = default;
    SystemManagerImpl(const SystemManagerImpl&) = delete;
    SystemManagerImpl(SystemManager&&) = delete;
    SystemManagerImpl& operator=(const SystemManagerImpl&) = delete;
    SystemManagerImpl& operator=(SystemManagerImpl&&) = delete;

    void init(SystemManager&, World&);
    void update(World&);
    void shutdown();

    template<typename T>
    T& getSystem();

    template<typename SystemsList>
    void registerSystems() noexcept;

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

    return *static_cast<T*>(systems_[iter->second]);
}

template<typename SystemsList>
void SystemManagerImpl::registerSystems() noexcept
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
            auto& system{systems_.emplace_back(std::make_unique<Ts>())};
            systemById_.emplace(std::type_index{ typeid(Ts) }, system.get());
        }(), ...);
    } };

    f(SystemsList{});
}
