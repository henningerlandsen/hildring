#include "catch.hpp"

#include "ecs/Systems.h"

#include <string>

SCENARIO("Registering components")
{
    GIVEN("A System is registered")
    {
        struct Component {
            std::string name;
        };

        struct System {
            System() {}
        };

        ecs::Systems::create<System>();

        WHEN("Registering a Component")
        {
            //            ecs::Systems::registerComponent<System, Component>();
            CHECK(false);
        }
    }
}

