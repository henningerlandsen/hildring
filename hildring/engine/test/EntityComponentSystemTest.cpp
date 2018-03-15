#include "catch.hpp"

#include "EntityComponentSystem.h"

TEST_CASE("Entity component system")
{
    SECTION("It creates component on registration")
    {
        struct ComponentMock {
            ComponentMock(bool* createFlag)
            {
                *createFlag = true;
            }
        };

        ecs::System system;
        bool created = false;
        system.addComponentHandler<ComponentMock>(&created);
        REQUIRE(created);
    }

    SECTION("It keeps the component alive")
    {
        struct ComponentMock {
            ComponentMock(bool* aliveFlag)
                : aliveFlag(aliveFlag)
            {
            }

            ~ComponentMock() { *aliveFlag = false; }

            bool* aliveFlag;
        };

        ecs::System system;
        bool componentAlive = true;
        system.addComponentHandler<ComponentMock>(&componentAlive);

        REQUIRE(componentAlive);
    }
}
