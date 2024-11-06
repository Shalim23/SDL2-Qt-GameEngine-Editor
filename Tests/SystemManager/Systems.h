#pragma once
#include <Engine/ECS/Types/SystemBase.h>

class SystemA : public SystemBase
{
public:
    virtual void init(SystemManager&, World&) override
    {
        value_ = 42;
    }

    virtual void update(World&) override
    {
        value_ = 42 * 2;
    }

    virtual void shutdown() override
    {
        value_ = -1;
    }

    int getValue() const { return value_; }

private:
    int value_{0};
};

class SystemB : public SystemBase
{

};
