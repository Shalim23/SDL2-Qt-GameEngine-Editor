#pragma once

class World;
class SystemManager;

class SystemBase
{
public:
    virtual void init(SystemManager&, World&){}
    virtual void update(World&){}
    virtual void shutdown(){}
};
