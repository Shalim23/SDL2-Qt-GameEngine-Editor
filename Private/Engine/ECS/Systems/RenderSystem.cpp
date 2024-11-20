#include "RenderSystem.h"
#include <cassert>
#include <stdexcept>

void RenderSystem::render()
{

}

void RenderSystem::createWindow()
{
    assert(window_ == nullptr && "Window is already created!");
    assert(renderer_ == nullptr && "Renderer is already created!");
    if (window_ && renderer_)
    {
        return;
    }

    constexpr Uint32 fullscreenFlag{ 0 };
    //constexpr Uint32 fullscreenFlag{ SDL_WINDOW_FULLSCREEN_DESKTOP };

    //#TODO name from config
    window_ = SDL_CreateWindow(" ", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 1920, 1080, fullscreenFlag);
    if (!window_)
    {
        throw std::runtime_error{"Failed to create SDL window!"};
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_)
    {
        throw std::runtime_error{ "Failed to create SDL renderer!" };
    }
}

void RenderSystem::shutdown()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    renderer_ = nullptr;
    window_ = nullptr;
}
