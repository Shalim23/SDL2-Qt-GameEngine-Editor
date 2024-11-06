#pragma once

#include "ECS/SystemManager.h"
#include "ECS/World.h"

class Engine final
{
public:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = delete;

    void init();
    void runFrame();
    void shutdown();

    template<typename SystemsList>
    void registerSystems();

private:
    SystemManager sm_;
    World world_;
};

template<typename SystemsList>
void Engine::registerSystems()
{
    static_assert(std::enable_if_t<IsTypesList<SystemsList>::value, void>,
        "TypesList is expected!");
    //#TODO concat with engine systems
    sm_.registerSystems<SystemsList>();
}
