#pragma once
#include "../../Private/ECS/Types/ComponentID.h"

#define COMPONENT_ID_GETTER(ComponentName) \
    static consteval ComponentID getComponentID() { return generateComponentID(#ComponentName); }
