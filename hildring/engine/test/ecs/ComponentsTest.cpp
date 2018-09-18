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
            auto result = ecs::Components::add<System, Component>();
            THEN("result is true")
            {
                CHECK(result);
            }
        }
    }
}

