#include "SystemManager.h"
#include "Engine/ECS/Types/SystemBase.h"

namespace
{
#define FOR_EACH_SYSTEM \
for(size_t i{0}; i < alignment_ * systemsCount_; i += alignment_)

#define SYSTEM_PTR \
reinterpret_cast<SystemBase*>(systems_.get() + i)
}

void SystemManager::init(SystemInitContext& context)
{
    FOR_EACH_SYSTEM
    {
        SYSTEM_PTR->init(context);
    }
}

void SystemManager::update(SystemUpdateContext& context)
{
    FOR_EACH_SYSTEM
    {
        SYSTEM_PTR->update(context);
    }
}

void SystemManager::shutdown()
{
    FOR_EACH_SYSTEM
    {
        SYSTEM_PTR->shutdown();
    }
}
