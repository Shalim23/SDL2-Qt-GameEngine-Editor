#pragma once
#include "../../Private/ECS/Types/ComponentIdGenerator.h"

#define COMPONENT_ID_GETTER(ComponentName) \
    static consteval ComponentId getComponentId() { return generateComponentId(#ComponentName); }
