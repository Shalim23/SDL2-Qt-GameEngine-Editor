#include "Engine/Engine.h"
#include "SDL.h"

Engine::~Engine()
{
    shutdown();
}

void Engine::runFrame()
{
    //update InputSystem separately here

    sm_.update(world_);

    renderSystem_->render();

    if (world_.getEntitiesWithComponent<StopEngineComponent>().size() > 0)
    {
        stop();
    }
}

void Engine::shutdown()
{
    if (state_ == EngineState::Stopped)
    {
        sm_.shutdown();
        shutdownSDL();
    }

    state_ = EngineState::None;
}

void Engine::run()
{
    SDL_assert(state_ == EngineState::Initialized);

    constexpr float targetFrameTime{1.0f / 60.0f};

    while (state_ != EngineState::Stopped)
    {
        const auto frameTimeStart{ SDL_GetPerformanceCounter() };

        runFrame();

        const auto frameTimeEnd{ SDL_GetPerformanceCounter() };
        dt_ = (frameTimeEnd - frameTimeStart)
            / static_cast<float>(SDL_GetPerformanceFrequency());

        if (dt_ < targetFrameTime)
        {
            SDL_Delay(static_cast<Uint32>((targetFrameTime - dt_) * 1000.0f));
        }
    }

    shutdown();
}

void Engine::stop()
{
    state_ = EngineState::Stopped;
}

void Engine::initSDL() const
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_FUNCTION, "Failed to init SDL!", nullptr);
        throw std::runtime_error{"Failed to init SDL!"};
    }
}

void Engine::shutdownSDL() const
{
    SDL_Quit();
}
