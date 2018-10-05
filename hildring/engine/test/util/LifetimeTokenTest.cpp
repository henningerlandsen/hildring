#include "catch.hpp"

#include "util/LifetimeToken.h"

SCENARIO("Destructor callback is invoked")
{
    GIVEN("LifetimeToken is crated with a callback")
    {
        bool called = false;
        auto tokenPtr = std::make_unique<util::LifetimeToken>([&called]() {
            called = true;
        });
        WHEN("LifetimeToken expires")
        {
            tokenPtr.reset();
            THEN("callback is invoked")
            {
                CHECK(called);
            }
        }
    }
}
