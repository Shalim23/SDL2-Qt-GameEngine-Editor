#include "SystemManagerImpl.h"

void SystemManagerImpl::init(SystemManager& sm, World& w) const noexcept
{
    for (auto& s : systems_)
    {
        s->init(sm, w);
    }
}

void SystemManagerImpl::update(World& w) const noexcept
{
    for (auto& s : systems_)
    {
        s->update(w);
    }
}

void SystemManagerImpl::shutdown() const noexcept
{
    for (auto& s : systems_)
    {
        s->shutdown();
    }
}
