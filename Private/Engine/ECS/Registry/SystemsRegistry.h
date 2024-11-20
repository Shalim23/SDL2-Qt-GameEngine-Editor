#pragma once
#include <Engine/ECS/Types/TypesList.h>

#include "Engine/ECS/Systems/SDLEventsSystem.h"
#include "../Systems/RenderSystem.h"

using EngineSystems = TypesList<SDLEventsSystem, RenderSystem>;
