#pragma once

class SystemInitContext;
class SystemUpdateContext;

class SystemBase
{
public:
    virtual void init(SystemInitContext&){}
    virtual void update(SystemUpdateContext&){}
    virtual void shutdown(){}
};
