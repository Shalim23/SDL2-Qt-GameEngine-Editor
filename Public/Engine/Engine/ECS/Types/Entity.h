#pragma once

class Entity
{
public:
    explicit Entity(const uint32_t id)
        : id_{id}, components_{}
    {}

    ~Entity() = default;
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    Entity(Entity&& other) noexcept
        : id_{ other.id_ }, components_{ std::move(other.components_) }
    {}

    Entity& operator=(Entity&& other) noexcept 
    {
        if (this != &other)
        {
            id_ = other.id_;
            components_ = std::move(other.components_);
        }
        return *this;
    }

    uint32_t getId() const noexcept
    {
        return id_;
    }

    const std::vector<ComponentID>& getComponents() const noexcept
    {
        return components_;
    }

private:

    uint32_t id_;
    std::vector<ComponentID> components_;
};
