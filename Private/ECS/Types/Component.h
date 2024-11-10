#pragma once
#include "ComponentID.h"
#include <memory>

template<typename T>
struct Component
{
    Entity entity;
    T instance;
};

struct ComponentsListBase
{
};

template<typename T>
class ComponentsList : ComponentsListBase
{
    std::vector<Component<T>> components_;
};

struct Components
{
    ComponentID id;
    std::unique_ptr<ComponentsListBase> components;
};
