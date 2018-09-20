#include "catch.hpp"

#include "ecs/Components.h"
#include "ecs/Systems.h"

#include <string>

SCENARIO("Registering components")
{
    struct Component {
        std::string name;
    };

    struct System {
        System() {}
    };

    GIVEN("System is not created")
    {
        WHEN("linking Component")
        {
            const auto result = ecs::Components<Component>::link<System>();
            THEN("linking fails")
            {
                CHECK(result == false);
            }
        }
    }

    GIVEN("System is created")
    {
        ecs::Systems::create<System>();

        WHEN("linking a Component")
        {
            const auto result = ecs::Components<Component>::link<System>();
            THEN("linking succeeds")
            {
                CHECK(result);
            }
        }

        WHEN("component is already linked")
        {
            const auto result = ecs::Components<Component>::link<System>();
            THEN("linking fails")
            {
                CHECK(result == false);
            }
        }
    }
}

