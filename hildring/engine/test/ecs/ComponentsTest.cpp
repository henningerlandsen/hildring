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

        bool create(const ecs::EntityId, Component*& c)
        {
            createCalled = true;
            c = &component;
            return true;
        }

        bool get(const ecs::EntityId, Component*& c)
        {
            c = &component;
            return true;
        }

        bool destroy(const ecs::EntityId)
        {
            destroyCalled = true;
            return true;
        }

        bool createCalled{ false };
        bool destroyCalled{ false };
        Component component;
    };

    GIVEN("Component and System is not linked")
    {
        WHEN("trying to create Component")
        {
            const auto result = ecs::Components<Component>::with(13, [](Component&) {});
            THEN("create fails")
            {
                CHECK(result == false);
            }
        }

        WHEN("trying to access Component")
        {
            const auto result = ecs::Components<Component>::create(42);
            THEN("accessing fails")
            {
                CHECK(result == false);
            }
        }

        WHEN("trying to delete Component")
        {
            const auto result = ecs::Components<Component>::destroy(42);
            THEN("delete fails")
            {
                CHECK(result == false);
            }
        }
    }

    GIVEN("System is not created")
    {
        WHEN("linking Component")
        {
            auto linkResult = ecs::Components<Component>::link<System>();
            THEN("linking succeeds")
            {
                CHECK(linkResult);
            }

            WHEN("creating Component")
            {
                const auto createResult = ecs::Components<Component>::create(42);
                THEN("create fails")
                {
                    CHECK(createResult == false);
                }
            }

            WHEN("accessing Component")
            {
                const auto result = ecs::Components<Component>::with(
                    42,
                    [](Component&) { CHECK(false); });
                THEN("accessing fails")
                {
                    CHECK(result == false);
                }
            }

            WHEN("deleting Component")
            {
                const auto result = ecs::Components<Component>::destroy(42);
                THEN("delete fails")
                {
                    CHECK(result == false);
                }
            }

            WHEN("System is created")
            {
                auto token = ecs::Systems<System>::create();

                THEN("Component can be created")
                {
                    const auto createResult = ecs::Components<Component>::create(42);
                    CHECK(createResult);
                }

                WHEN("lifetime token is moved")
                {
                    {
                        const auto linkResultCopy = std::move(linkResult);
                        THEN("link still exists")
                        {
                            CHECK(ecs::Components<Component>::create(42) == true);
                        }
                    }
                    WHEN("moved token is destroyed")
                    {
                        THEN("link is broken")
                        {
                            CHECK(ecs::Components<Component>::create(42) == false);
                        }
                    }
                }
            }
        }
    }

    GIVEN("System is created")
    {
        auto token = ecs::Systems<System>::create();

        WHEN("linking a Component")
        {
            const auto linkResult = ecs::Components<Component>::link<System>();
            THEN("linking succeeds")
            {
                CHECK(linkResult);
            }

            WHEN("Component is created")
            {
                bool didRunInit = false;
                const auto didCreate = ecs::Components<Component>::create(
                    42,
                    [&didRunInit](Component&) {
                        didRunInit = true;
                    });

                THEN("System creates it")
                {
                    ecs::Systems<System>::with([](System& system) {
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

                THEN("Component can be accessed")
                {
                    CHECK(ecs::Components<Component>::with(42, [](Component& c) {
                        c.name = "Dingo";
                    }));
                    CHECK(ecs::Systems<System>::with([](System& s) {
                        CHECK(s.component.name == "Dingo");
                    }));
                }

                WHEN("Component is deleted")
                {
                    CHECK(ecs::Components<Component>::destroy(42));

                    THEN("Systems destroy is called")
                    {
                        CHECK(ecs::Systems<System>::with([](System& s) {
                            CHECK(s.destroyCalled);
                        }));
                    }
                }
            }

            WHEN("component is already linked")
            {
                const auto linkResult2 = ecs::Components<Component>::link<System>();
                THEN("linking fails")
                {
                    CHECK(linkResult2 == false);
                }
            }
        }
    }

    GIVEN("System cannot allocate")
    {
        struct BadAllocSystem {
            bool create(const ecs::EntityId, int*&)
            {
                return false;
            }

            bool get(const ecs::EntityId, int*&) { return false; }

            bool destroy(const ecs::EntityId) { return false; }
        };

        auto token = ecs::Systems<BadAllocSystem>::create();
        const auto linkResult = ecs::Components<int>::link<BadAllocSystem>();

        WHEN("creating component")
        {
            const auto result = ecs::Components<int>::create(42);
            THEN("create fails")
            {
                CHECK(result == false);
            }
        }

        WHEN("accessing component")
        {
            const auto result = ecs::Components<int>::with(11, [](int&) {});
            THEN("it cannot access non-existing component")
            {
                CHECK(result == false);
            }
        }

        WHEN("destroying component")
        {
            const auto result = ecs::Components<int>::destroy(0);
            THEN("it cannot destroy non-existing component")
            {
                CHECK(result == false);
            }
        }
    }
}

