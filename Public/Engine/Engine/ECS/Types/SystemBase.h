#pragma once

class SystemManager;
class World;

class SystemBase
{
public:
    virtual void init(SystemManager&, World&){}
    virtual void update(World&){}
    virtual void shutdown(){}
};
