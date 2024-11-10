#pragma once
#include "Engine/ECS/Types/Entity.h"

template<typename T>
class Component
{
public:
    Component(const Entity e) : e_{e}, c_{}
    {}

    Entity getEntity() const { return e_; }
    T& get() { return c_; }

private:
    Entity e_;
    T c_;
};
