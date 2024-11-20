#pragma once
#include "../Types/SystemBase.h"

class SDLEventsSystem : public SystemBase
{
//#TODO
//callback for different events
public:
    virtual void update(World& world) override;
};
