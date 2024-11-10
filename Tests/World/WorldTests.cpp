#include <gtest/gtest.h>
#include <Engine/ECS/World.h>
#include "Components.h"

TEST(WorldTests, DoubleComponentsRegistration)
{
    using TestComponents = TypesList<TestComponentA>;

    World w;
    w.registerComponents<TestComponents>();
    EXPECT_THROW(w.registerComponents<TestComponents>(), std::logic_error);
}

TEST(WorldTests, CreateEntity)
{
    World w;
    ASSERT_EQ(w.getEntities().size(), 0);
    w.createEntity();
    ASSERT_EQ(w.getEntities().size(), 1);
}

TEST(WorldTests, DestroyEntity)
{
    World w;
    ASSERT_EQ(w.getEntities().size(), 0);
    auto e{w.createEntity()};
    ASSERT_EQ(w.getEntities().size(), 1);
    w.destroyEntity(e);
    ASSERT_EQ(w.getEntities().size(), 0);
}
