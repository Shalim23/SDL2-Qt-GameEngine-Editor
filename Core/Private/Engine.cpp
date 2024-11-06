#include "Engine/Engine.h"

void Engine::init()
{
    sm_.init(world_);
}

void Engine::runFrame()
{
    sm_.update(world_);
}

void Engine::shutdown()
{
    sm_.shutdown();
}
