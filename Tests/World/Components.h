#pragma once
#include <Engine/ECS/Types/Component.h>

struct TestComponentA
{
    COMPONENT_ID_GETTER(TestComponentA)

    int value{0};
};
