#include "RenderSystem.h"
#include <stdexcept>

void RenderSystem::render()
{

}

void RenderSystem::createWindow()
{
    SDL_assert(window_ == nullptr && "Window is already created!");
    SDL_assert(renderer_ == nullptr && "Renderer is already created!");
    if (window_ && renderer_)
    {
        return;
    }

    constexpr Uint32 fullscreenFlag{ 0 };
    //constexpr Uint32 fullscreenFlag{ SDL_WINDOW_FULLSCREEN_DESKTOP };

    //#TODO name from config
    window_ = SDL_CreateWindow(" ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, fullscreenFlag);
    if (!window_)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_FUNCTION, "Failed to create SDL window!", nullptr);
        throw std::runtime_error{"Failed to create SDL window!"};
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_FUNCTION, "Failed to create SDL renderer!", window_);
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
