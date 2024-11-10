#include "SystemManagerImpl.h"

void SystemManagerImpl::init(SystemManager& sm, World& w) const noexcept
{
    for (auto& s : systems_)
    {
        s.system->init(sm, w);
    }
}

void SystemManagerImpl::update(World& w) const noexcept
{
    for (auto& s : systems_)
    {
        s.system->update(w);
    }
}

void SystemManagerImpl::shutdown() const noexcept
{
    for (auto& s : systems_)
    {
        s.system->shutdown();
    }
}
