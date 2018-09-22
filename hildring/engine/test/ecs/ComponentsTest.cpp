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
            THEN("linking succeeds")
            {
                CHECK(result);
            }

            WHEN("creating Component")
            {
                const auto result = ecs::Components<Component>::create();
                THEN("create fails")
                {
                    CHECK(result == false);
                }
            }

            WHEN("System is created")
            {
                ecs::Systems::create<System>();

                THEN("Component can be created")
                {
                    const auto result = ecs::Components<Component>::create();
                    CHECK(result);
                }
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

    GIVEN("System cannot allocate")
    {
        struct BadAllocSystem {
            bool create(int*&)
            {
                return false;
            }
        };

        ecs::Systems::create<BadAllocSystem>();
        const auto linkResult = ecs::Components<int>::link<BadAllocSystem>();

        WHEN("creating component")
        {
            const auto result = ecs::Components<int>::create();
            THEN("create fails")
            {
                CHECK(result == false);
            }
        }
    }
}

