#pragma once
#include "Component.h"
#include <stdexcept>

class ComponentsBase
{
public:
    virtual void removeComponent(const Entity) = 0;
};

template<typename T>
class Components : public ComponentsBase
{
public:
    void removeComponent(const Entity e) override
    {
        const auto iter{ indexByEntity_.find(e) };
        if (iter == indexByEntity_.end())
        {
            throw std::logic_error{ "Cannot find component index for entity!" };
        }

        const auto index{ iter->second };
        auto& componentToRemove{components_[index]};
        if (componentToRemove.getEntity() != e)
        {
            throw std::logic_error{ "Wrong component index for entity!" };
        }

        if (index == components_.size() - 1)
        {
            components_.pop_back();
            indexByEntity_.erase(e);
            return;
        }

        auto& componentToSwap{ components_.back() };
        auto iterToUpdate{ indexByEntity_.find(componentToSwap.getEntity()) };
        if (iterToUpdate == indexByEntity_.end())
        {
            throw std::logic_error{ "Cannot find component index for entity!" };
        }

        iterToUpdate->second = index;
        std::swap(componentToRemove, componentToSwap);

        components_.pop_back();
        indexByEntity_.erase(e);
    }

private:
    std::vector<Component<T>> components_;
    std::unordered_map<Entity, size_t> indexByEntity_;
};
