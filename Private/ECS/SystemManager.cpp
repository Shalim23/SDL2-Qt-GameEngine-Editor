#include "SystemManager.h"

void SystemManager::init(SystemInitContext& context)
{
    for (auto& system : systems_)
    {
        system->init(context);
    }
}

void SystemManager::update(SystemUpdateContext& context)
{
    for (auto& system : systems_)
    {
        system->update(context);
    }
}

void SystemManager::shutdown()
{
    for (auto& system : systems_)
    {
        system->shutdown();
    }
}
