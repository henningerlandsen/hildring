#include "catch.hpp"

#include "util/Index.h"
/*
 * Given a default initialized index
 *  - Then it is not valid
 *  
 *  - When assigning a value
 *  - Then it is valid
 * */
SCENARIO("Invalid index")
{
    GIVEN("A default initialized Index")
    {
        auto index = util::Index<int, -1>{};

        THEN("Index is not valid")
        {
            CHECK(!index.valid());
        }

        WHEN("Assigning a value")
        {
            index = 1;

            THEN("Index is valid")
            {
                CHECK(index.valid());
            }
        }

        WHEN("Assigning a different value")
        {
            index = 0;

            THEN("Index is valid")
            {
                CHECK(index.valid());
            }
        }
    }
}

SCENARIO("Valid Index")
{
    GIVEN("A value initialized index")
    {
        auto index = util::Index<int, -1>{ 1 };

        THEN("Index is valid")
        {
            CHECK(index.valid());
        }

        THEN("Value can be read")
        {
            CHECK(index == 1);
        }

        WHEN("Index is invalidated")
        {
            index.invalidate();

            THEN("It is not valid")
            {
                CHECK(!index.valid());
            }
        }
    }
}

SCENARIO("It works with any type")
{
    auto index = util::Index<bool, false>{};

    CHECK(!index.valid());

    index = true;

    CHECK(index.valid());

    index.invalidate();

    CHECK(!index.valid());
}
