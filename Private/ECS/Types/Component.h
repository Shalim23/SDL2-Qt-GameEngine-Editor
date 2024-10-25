#pragma once
#include "Engine/ECS/Types/Entity.h"

template<typename T>
struct Component
{
    Component(const Entity e) : entity{e}, component{}
    {}

    const Entity entity;
    T component;
};
