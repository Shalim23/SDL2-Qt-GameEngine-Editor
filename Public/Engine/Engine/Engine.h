#pragma once

#include "../Private/EngineImpl.h"

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
    void run();

    template<typename SystemsList>
    void registerSystems();

    template<typename ComponentsList>
    void registerComponents();

private:
    EngineImpl impl_;
};

template<typename SystemsList>
void Engine::registerSystems()
{
    impl_.registerSystems<SystemsList>();
}

template<typename ComponentsList>
void Engine::registerComponents()
{
    impl_.registerComponents<ComponentsList>();
}
