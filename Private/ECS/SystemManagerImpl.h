#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "Engine/ECS/Types/SystemBase.h"

class World;
class SystemManager;

class SystemManagerImpl final
{
public:
    SystemManagerImpl() = default;
    ~SystemManagerImpl() = default;
    SystemManagerImpl(const SystemManagerImpl& other) = delete;
    SystemManagerImpl(SystemManagerImpl&& other) = delete;
    SystemManagerImpl& operator=(const SystemManagerImpl& other) = delete;
    SystemManagerImpl& operator=(SystemManagerImpl&& other) = delete;

    void init(SystemManager&, World&);
    void update(World&);
    void shutdown();

    template<typename T>
    T& getSystem();

private:
    std::vector<std::unique_ptr<SystemBase>> systems_;
    std::unordered_map<std::type_index, size_t> systemIndexById_;
};

template<typename T>
T& SystemManagerImpl::getSystem()
{
    const auto iter{ systemIndexById_.find(std::type_index{typeid(T)}) };

    //#TODO https://github.com/Shalim23/SDL2-Qt-GameEngine-Editor/issues/1
    // fatal error if not found

    auto* system{ systems_[iter->second].get() };
    return *static_cast<T*>(system);
}
