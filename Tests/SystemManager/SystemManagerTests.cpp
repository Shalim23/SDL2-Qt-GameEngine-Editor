#include <gtest/gtest.h>
#include <Engine/ECS/SystemManager.h>
#include <Engine/ECS/World.h>
#include "Systems.h"

TEST(SystemManagerTests, DoubleSystemRegistration)
{
    using TestSystems = TypesList<SystemA>;

    SystemManager sm;
    sm.registerSystems<TestSystems>();
    EXPECT_THROW(sm.registerSystems<TestSystems>(), std::logic_error);
}

TEST(SystemManagerTests, GetNonRegisteredSystem)
{
    using TestSystems = TypesList<SystemA>;

    SystemManager sm;
    sm.registerSystems<TestSystems>();
    EXPECT_THROW(sm.getSystem<SystemB>(), std::logic_error);
}

TEST(SystemManagerTests, GetSystem)
{
    using TestSystems = TypesList<SystemA>;

    SystemManager sm;
    sm.registerSystems<TestSystems>();
    auto& system{sm.getSystem<SystemA>()};
    ASSERT_EQ(system.getValue(), 0);
}

TEST(SystemManagerTests, GetSystemInit)
{
    using TestSystems = TypesList<SystemA>;

    World w;
    SystemManager sm;
    sm.registerSystems<TestSystems>();
    auto& system{ sm.getSystem<SystemA>() };
    sm.init(w);
    ASSERT_EQ(system.getValue(), 42);
}

TEST(SystemManagerTests, GetSystemUpdate)
{
    using TestSystems = TypesList<SystemA>;

    World w;
    SystemManager sm;
    sm.registerSystems<TestSystems>();
    auto& system{ sm.getSystem<SystemA>() };
    sm.update(w);
    ASSERT_EQ(system.getValue(), 42 * 2);
}

TEST(SystemManagerTests, GetSystemShutdown)
{
    using TestSystems = TypesList<SystemA>;

    World w;
    SystemManager sm;
    sm.registerSystems<TestSystems>();
    auto& system{ sm.getSystem<SystemA>() };
    sm.shutdown();
    ASSERT_EQ(system.getValue(), -1);
}
