#include "ecs/Entity.h"
#include "ecs/Systems.h"

#include "catch.hpp"

SCENARIO("Create Entity")
{
    WHEN("an Entity is created")
    {
        auto e = ecs::Entity();

        THEN("it has a valid Id")
        {
            CHECK(e.id().valid());
        }
    }

    WHEN("two Entities are created")
    {
        auto e1 = ecs::Entity();
        auto e2 = ecs::Entity();

        THEN("they do not have the same id")
        {
            CHECK(e1.id() != e2.id());
        }
    }

    WHEN("an Entity is copied")
    {
        auto e = ecs::Entity();
        auto e2 = e;

        THEN("they have the same id")
        {
            CHECK(e.id() == e2.id());
        }
    }
}

SCENARIO("Entities have components")
{
    struct System {
        bool create(const ecs::EntityId id, int*& component)
        {
            CHECK(expectedId == id);
            component = &value;
            createCalled = true;
            return true;
        }

        bool get(const ecs::EntityId id, int*& component)
        {
            CHECK(expectedId == id);
            component = &value;
            getCalled = true;
            return true;
        }
        bool destroy(const ecs::EntityId id)
        {
            CHECK(expectedId == id);
            destroyCalled = true;
            return true;
        }

        ecs::EntityId expectedId = 0;
        bool createCalled = false;
        bool getCalled = false;
        bool destroyCalled = false;

        int value = 0;
    };

    GIVEN("an Entity and a Component linked to a System")
    {
        auto entity = ecs::Entity();
        auto token = ecs::Systems<System>::create();
        ecs::Systems<System>::with([entity](System& s) {
            s.expectedId = entity.id();
        });
        auto link = ecs::Components<int>::link<System>();

        WHEN("a Component is added to the Entity")
        {
            const auto result = entity.add<int>([](int& c) {
                c = 9;
            });

            THEN("return value is true")
            {
                CHECK(result == true);
            }

            THEN("System creates the Component")
            {
                CHECK(ecs::Systems<System>::with([](System& s) {
                    CHECK(s.createCalled);
                }));
            }

            THEN("Components value is updated")
            {
                CHECK(ecs::Systems<System>::with([](System& s) {
                    CHECK(s.value == 9);
                }));
            }

            THEN("Component can be accessed")
            {
                CHECK(entity.with<int>([](int&) {}));
                CHECK(ecs::Systems<System>::with([](System& s) {
                    CHECK(s.getCalled);
                }));
            }

            THEN("Component can be removed")
            {
                CHECK(entity.destroy<int>());
                CHECK(ecs::Systems<System>::with([](System& s) {
                    CHECK(s.destroyCalled);
                }));
            }
        }
    }
}
