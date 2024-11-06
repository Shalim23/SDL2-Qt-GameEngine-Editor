#include "Engine/Engine.h"


void Engine::init()
{
    impl_.init();
}

void Engine::runFrame()
{
    impl_.runFrame();
}

void Engine::shutdown()
{
    impl_.shutdown();
}

void Engine::run()
{
    impl_.run();
}
