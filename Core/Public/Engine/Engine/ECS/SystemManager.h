#pragma once

#include "../../Private/ECS/SystemManagerImpl.h"

class World;

class SystemManager final
{
public:
    SystemManager() = default;
    ~SystemManager() = default;
    SystemManager(const SystemManager&) = delete;
    SystemManager(SystemManager&&) = delete;
    SystemManager& operator=(const SystemManager&) = delete;
    SystemManager& operator=(SystemManager&&) = delete;

    void init(World&);
    void update(World&);
    void shutdown();

    template<typename T>
    T& getSystem();

    template<typename SystemsList>
    void registerSystems();

private:
    SystemManagerImpl impl_;
};

template<typename T>
T& SystemManager::getSystem()
{
    return impl_.getSystem<T>();
}

template<typename SystemsList>
void SystemManager::registerSystems()
{
    impl_.registerSystems<SystemsList>();
}
