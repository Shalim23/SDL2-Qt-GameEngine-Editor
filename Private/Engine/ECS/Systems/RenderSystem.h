#pragma once
#include "Engine/ECS/Types/SystemBase.h"
#include "SDL.h"

class RenderSystem : public SystemBase
{
public:
    void render();
    void createWindow();

    virtual void shutdown() override;

private:
    SDL_Window* window_{ nullptr };
    SDL_Renderer* renderer_{ nullptr };
};
