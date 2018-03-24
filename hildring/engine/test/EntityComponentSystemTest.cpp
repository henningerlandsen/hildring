#include "catch.hpp"

#include "EntityComponentSystem.h"

TEST_CASE("Entity component system")
{
    struct AliveTracker {
        explicit AliveTracker(bool* aliveFlag)
            : aliveFlag(aliveFlag)
        {
            *aliveFlag = true;
        }

        ~AliveTracker() { *aliveFlag = false; }

        bool* aliveFlag;
    };

    SECTION("It creates component on registration")
    {
        struct ComponentMock {
            explicit ComponentMock(bool* createFlag)
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
        ecs::System system;
        bool componentAlive = true;
        system.addComponentHandler<AliveTracker>(&componentAlive);

        REQUIRE(componentAlive);
    }

    SECTION("It stores multiple components")
    {
        ecs::System system;
        bool alive1 = false;
        bool alive2 = false;

        system.addComponentHandler<AliveTracker>(&alive1);
        system.addComponentHandler<AliveTracker>(&alive2);

        REQUIRE(alive1);
        REQUIRE(alive2);
    }

}
