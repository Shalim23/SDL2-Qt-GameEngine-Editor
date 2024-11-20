#include "Engine/ECS/Systems/SDLEventsSystem.h"
#include "Engine/ECS/World.h"
#include "Engine/ECS/Components/StopEngineComponent.h"
#include "SDL.h"

void SDLEventsSystem::update(World& world)
{
    SDL_Event currentEvent;
    while (SDL_PollEvent(&currentEvent))
    {
        switch (currentEvent.type)
        {
            case SDL_QUIT:
            {
                const auto entity{world.createEntity()};
                world.addComponent<StopEngineComponent>(entity);
                break;
            }
        }
    }
}
