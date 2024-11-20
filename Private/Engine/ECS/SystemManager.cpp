#include "Engine/ECS/SystemManager.h"

void SystemManager::init(World& w) noexcept
{
    for (auto& s : systems_)
    {
        s.system->init(*this, w);
    }
}

void SystemManager::update(World& w) const noexcept
{
    for (auto& s : systems_)
    {
        s.system->update(w);
    }
}

void SystemManager::shutdown() const noexcept
{
    for (auto& s : systems_)
    {
        s.system->shutdown();
    }
}
