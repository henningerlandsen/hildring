#include "catch.hpp"

#include "ecs/Components.h"
#include "ecs/Systems.h"

#include <string>

SCENARIO("Registering components")
{
    GIVEN("a System is registered")
    {
        struct Component {
            std::string name;
        };

        struct System {
            System() {}
        };

        ecs::Systems::create<System>();

        WHEN("registering a Component")
        {
            auto result = ecs::Components<Component>::link<System>();
            THEN("result is true")
            {
                CHECK(result);
            }
        }

        WHEN("component is already registered")
        {
            auto result = ecs::Components<Component>::link<System>();
            THEN("result is false")
            {
                CHECK(result == false);
            }
        }
    }
}

