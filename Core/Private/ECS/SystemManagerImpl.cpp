#include "SystemManagerImpl.h"

void SystemManagerImpl::init(SystemManager& sm, World& w)
{
    for (auto& s : systems_)
    {
        s->init(sm, w);
    }
}

void SystemManagerImpl::update(World& w)
{
    for (auto& s : systems_)
    {
        s->update(w);
    }
}

void SystemManagerImpl::shutdown()
{
    for (auto& s : systems_)
    {
        s->shutdown();
    }
}
