#pragma once

#include "Engine/ECS/SystemManager.h"
#include "Engine/ECS/World.h"
#include "../../Private/Engine/Types/EngineState.h"
#include "../../Private/Engine/ECS/Types/TypesListOperations.h"
#include "../../Private/Engine/ECS/Registry/ComponentsRegistry.h"
#include "../../Private/Engine/ECS/Registry/SystemsRegistry.h"

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

    float dt_{};
};

template<typename SystemsList, typename ComponentsList>
void Engine::init()
{
    assert(state_ == EngineState::None);

    {
        static_assert(IsTypesList<SystemsList>::value, "TypesList is expected!");
        using AllSystems = Concatenate<SystemsList, EngineSystems>::type;
        sm_.registerSystems<AllSystems>();
    }

    {
        static_assert(IsTypesList<ComponentsList>::value, "TypesList is expected!");
        using AllComponents = Concatenate<ComponentsList, EngineComponents>::type;
        world_.registerComponents<AllComponents>();
    }

    sm_.init(world_);

    state_ = EngineState::Initialized;
}
