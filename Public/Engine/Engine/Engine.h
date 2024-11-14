#pragma once

#include "Engine/ECS/SystemManager.h"
#include "Engine/ECS/World.h"
#include "../../Private/Types/EngineState.h"

class Engine final
{
public:
    Engine() = default;
    ~Engine();
    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = delete;

    template<typename SystemsList, typename ComponentsList>
    void init();

    void runFrame();
    void shutdown();
    void run();

private:
    void stop();

private:
    SystemManager sm_;
    World world_;
    EngineState state_{ EngineState::None };
};

template<typename SystemsList, typename ComponentsList>
void Engine::init()
{
    assert(state_ == EngineState::None);

    {
        static_assert(IsTypesList<SystemsList>::value, "TypesList is expected!");
        //#TODO concat with engine systems
        sm_.registerSystems<SystemsList>();
    }

    {
        static_assert(IsTypesList<ComponentsList>::value, "TypesList is expected!");
        //#TODO concat with engine components
        world_.registerComponents<ComponentsList>();
    }

    sm_.init(world_);

    state_ = EngineState::Initialized;
}
