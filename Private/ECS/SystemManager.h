#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "Engine/ECS/Types/SystemBase.h"

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

private:
    std::vector<std::unique_ptr<SystemBase>> systems_;
    std::unordered_map<std::type_index, size_t> systemIndexById_;
};

template<typename T>
T& SystemManager::getSystem()
{
    const auto iter{ systemIndexById_.find(std::type_index{typeid(T)}) };

    //#TODO https://github.com/Shalim23/SDL2-Qt-GameEngine-Editor/issues/1
    // fatal error if not found

    auto* system{ systems_[iter->second].get() };
    return *static_cast<T*>(system);
}
