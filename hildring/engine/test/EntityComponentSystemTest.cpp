#include "catch.hpp"

#include "EntityComponentSystem.h"

TEST_CASE("Entity component system")
{
    struct Component {
        Component(bool* createFlag)
        {
            *createFlag = true;
        }
    };

    SECTION("It creates component on registration")
    {
        ecs::System system;
        bool created = false;
        system.addComponentHandler<Component>(&created);
        REQUIRE(created);
    }
}
