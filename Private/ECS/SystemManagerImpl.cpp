#include "SystemManagerImpl.h"

void SystemManagerImpl::init(SystemManager& sm, World& w)
{
    for (auto& system : systems_)
    {
        system->init(sm, w);
    }
}

void SystemManagerImpl::update(World& w)
{
    for (auto& system : systems_)
    {
        system->update(w);
    }
}

void SystemManagerImpl::shutdown()
{
    for (auto& system : systems_)
    {
        system->shutdown();
    }
}
