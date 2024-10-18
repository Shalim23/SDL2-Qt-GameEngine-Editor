#pragma once

class World;
class SystemManager;

class SystemUpdateContext
{
public:
    SystemUpdateContext(World& w)
    : w_{w}
    {}

private:
    World& w_;
};

class SystemInitContext : public SystemUpdateContext
{
public:
    SystemInitContext(SystemManager& sm, World& w)
    : SystemUpdateContext{w}
    , sm_{sm}
    {}

    template<typename T>
    T& getSystem()
    {
        return sm_.getSystem<T>();
    }

private:
    SystemManager& sm_;
};
