#include "ecs/Entity.h"

#include "catch.hpp"

SCENARIO("Create Entity")
{
    WHEN("an Entity is created")
    {
        auto e = ecs::Entity();

        THEN("it has a valid Id")
        {
            CHECK(e.getId().valid());
        }
    }

    WHEN("two Entities are created")
    {
        auto e1 = ecs::Entity();
        auto e2 = ecs::Entity();

        THEN("they do not have the same id")
        {
            CHECK(e1.getId() != e2.getId());
        }
    }

    WHEN("an Entity is copied")
    {
        auto e = ecs::Entity();
        auto e2 = e;

        THEN("they have the same id")
        {
            CHECK(e.getId() == e2.getId());
        }
    }
}
