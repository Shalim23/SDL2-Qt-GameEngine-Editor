#pragma once

#include "Private/ECS/SystemManagerImpl.h"

class World;

class SystemManager final
{
public:
    SystemManager() = default;
    ~SystemManager() = default;
    SystemManager(const SystemManager& other) = delete;
    SystemManager(SystemManager&& other) = delete;
    SystemManager& operator=(const SystemManager& other) = delete;
    SystemManager& operator=(SystemManager&& other) = delete;

    void init(World&);
    void update(World&);
    void shutdown();

    template<typename T>
    T& getSystem();

private:
    SystemManagerImpl impl_{};
};

template<typename T>
T& SystemManager::getSystem()
{
    return impl_.getSystem<T>();
}
