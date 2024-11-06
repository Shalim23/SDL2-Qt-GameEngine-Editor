#include "Engine/ECS/SystemManager.h"

void SystemManager::init(World& w)
{
    impl_.init(*this, w);
}

void SystemManager::update(World& w)
{
    impl_.update(w);
}

void SystemManager::shutdown()
{
    impl_.shutdown();
}
