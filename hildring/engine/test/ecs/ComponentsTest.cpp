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

        bool create(Component*& c)
        {
            createCalled = true;
            c = &component;
            return true;
        }

        bool createCalled = false;
        Component component;
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

        WHEN("creating Component")
        {
            bool didRunInit = false;
            const auto didCreate = ecs::Components<Component>::create(
                [&didRunInit](Component&) {
                    didRunInit = true;
                });

            THEN("System creates it")
            {
                ecs::Systems::with<System>([](System& system) {
                    CHECK(system.createCalled);
                });
            }

            THEN("init method is called")
            {
                CHECK(didRunInit);
            }

            THEN("Component exists")
            {
                CHECK(didCreate);
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

