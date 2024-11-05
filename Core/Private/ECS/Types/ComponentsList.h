#pragma once
#include "Engine/ECS/Types/Entity.h"

//struct ComponentsListBase
//{
//    virtual void removeComponent(const Entity) = 0;
//};
//
//template<typename T>
//struct ComponentsList : ComponentsListBase
//{
//    virtual void removeComponent(const Entity entity) override
//    {
//        const auto newEnd{std::ranges::remove_if(components,
//            [entity](const auto& component){ return component.entity == entity; })};
//        components.erase(newEnd, components.end());
//    }
//
//    template<typename T>
//    T& addComponent(const Entity entity)
//    {
//        return components.emplace_back(Component<T>{entity}).component;
//    }
//
//    T* tryGetComponent(const Entity entity, const size_t index)
//    {
//        auto iter{ std::ranges::find_if(components, [entity](const auto& component)
//            { return component.entity == entity; }) };
//
//        //#TODO https://github.com/Shalim23/SDL2-Qt-GameEngine-Editor/issues/1
//        // fatal error if not found
//
//        return iter->component;
//    }
//
//    std::vector<Component<T>> components;
//};
