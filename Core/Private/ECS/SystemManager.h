#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "Engine/ECS/Types/SystemBase.h"
#include "Types/TypesListOperations.h"

class SystemInitContext;
class SystemUpdateContext;

class SystemManager final
{
public:
    SystemManager() = default;
    ~SystemManager() = default;
    SystemManager(const SystemManager&) = delete;
    SystemManager(SystemManager&&) = delete;
    SystemManager& operator=(const SystemManager&) = delete;
    SystemManager& operator=(SystemManager&&) = delete;

    void init(SystemInitContext&);
    void update(SystemUpdateContext&);
    void shutdown();

    template<typename T>
    T& getSystem();

    template<typename SystemsList>
    void registerSystems();

private:
    std::vector<std::unique_ptr<SystemBase>> systems_;
    std::unordered_map<std::type_index, SystemBase*> systemsById_;
};

template<typename T>
T& SystemManager::getSystem()
{
    const auto iter{ systemsById_.find(std::type_index{typeid(T)}) };

    //#TODO https://github.com/Shalim23/SDL2-Qt-GameEngine-Editor/issues/1
    // fatal error if not found

    return *static_cast<T*>(systems_[iter->second]);
}

template<typename SystemsList>
void SystemManager::registerSystems()
{
    static_assert(SystemsList::size, "No systems to register!");
    checkDuplicates<SystemsList>();

    //#TODO https://github.com/Shalim23/SDL2-Qt-GameEngine-Editor/issues/1
    // warning if already registered

    systems_.reserve(SystemsList::size);

    auto f{ [this] <typename... Ts>(TypesList<Ts...>)
    {
        ([this]
        {
            auto& system{systems_.emplace_back(std::make_unique<Ts>())};
            systemsById_.emplace(std::type_index{ typeid(Ts) }, system.get());
        }(), ...);
    } };

    f(SystemsList{});
}
