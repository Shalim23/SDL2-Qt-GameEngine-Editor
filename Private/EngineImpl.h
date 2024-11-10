#pragma once

#include "Engine/ECS/SystemManager.h"
#include "Engine/ECS/World.h"
#include "../Private/Types/EngineState.h"

class EngineImpl final
{
public:
    EngineImpl() = default;
    ~EngineImpl();
    EngineImpl(const EngineImpl&) = delete;
    EngineImpl(EngineImpl&&) = delete;
    EngineImpl& operator=(const EngineImpl&) = delete;
    EngineImpl& operator=(EngineImpl&&) = delete;

    void init();
    void runFrame();
    void shutdown();
    void run();

    template<typename SystemsList>
    void registerSystems();

    template<typename ComponentsList>
    void registerComponents();

private:
    void stop();

private:
    SystemManager sm_;
    World world_;
    EngineState state_{EngineState::None};
};

template<typename SystemsList>
void EngineImpl::registerSystems()
{
    static_assert(std::enable_if_t<IsTypesList<SystemsList>::value, void>,
        "TypesList is expected!");
    //#TODO concat with engine systems
    sm_.registerSystems<SystemsList>();

    state_ = (state_ == EngineState::ComponentsRegistered)
        ? EngineState::AllRegistered : EngineState::SystemsRegistered;
}

template<typename ComponentsList>
void EngineImpl::registerComponents()
{
    static_assert(std::enable_if_t<IsTypesList<ComponentsList>::value, void>,
        "TypesList is expected!");
    //#TODO concat with engine components
    //world_.registerComponents<ComponentsList>();

    state_ = (state_ == EngineState::SystemsRegistered)
        ? EngineState::AllRegistered : EngineState::ComponentsRegistered;
}
