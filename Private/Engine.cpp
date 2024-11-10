#include "Engine/Engine.h"


Engine::~Engine()
{
    shutdown();
}

void Engine::init()
{
    if (state_ != EngineState::AllRegistered)
    {
        //throw std::logic_error{ "Systems and components must be registered before init!" };
    }

    sm_.init(world_);

    state_ = EngineState::Initialized;
}

void Engine::runFrame()
{
    //update InputSystem separately here

    sm_.update(world_);

    //render separately here

    //#TODO
    //smth like EngineComponent where stop can be requested
    //here check this component
}

void Engine::shutdown()
{
    if (state_ == EngineState::Stopped)
    {
        sm_.shutdown();
    }

    state_ = EngineState::None;
}

void Engine::run()
{
    if (state_ != EngineState::Initialized)
    {
        //throw std::logic_error{ "Init must be called before run!" };
    }

    while (state_ != EngineState::Stopped)
    {
        //loop with 60 FPS
        runFrame();
    }

    shutdown();
}

void Engine::stop()
{
    state_ = EngineState::Stopped;
}
