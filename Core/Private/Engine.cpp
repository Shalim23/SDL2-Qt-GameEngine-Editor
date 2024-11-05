#include "Engine/Engine.h"

Engine::Engine()
    : context_{sm_, world_}
{
}

void Engine::init()
{
    sm_.init(context_);
}

void Engine::runFrame()
{
    sm_.update(context_);
}

void Engine::shutdown()
{
    sm_.shutdown();
}
