#pragma once

#include "../../Private/ECS/SystemManager.h"
#include "../../Private/ECS/World.h"
#include "ECS/SystemContext.h"

class Engine final
{
public:
    Engine();
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
    SystemInitContext context_;
};

template<typename SystemsList>
void Engine::registerSystems()
{
    //#TODO concat with engine systems
    sm_.registerSystems<SystemsList>();
}
