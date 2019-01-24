#include "catch.hpp"

#include "util/LifetimeToken.h"

#include <type_traits>

SCENARIO("Destructor callback is invoked")
{
    bool called = false;
    auto callback = [&called]() {
        called = true;
    };

    GIVEN("LifetimeToken is crated with a callback")
    {
        auto tokenPtr = std::make_unique<util::LifetimeToken>(callback);
        WHEN("LifetimeToken expires")
        {
            tokenPtr.reset();
            THEN("callback is invoked")
            {
                CHECK(called);
            }
        }

        WHEN("LifetimeToken is explicitly released")
        {
            tokenPtr->release();

            THEN("callback is invoked")
            {
                CHECK(called);
            }
        }
    }

    GIVEN("a method that returns a token")
    {
        auto method = [callback]() {
            return util::LifetimeToken(callback);
        };

        WHEN("method is called")
        {
            util::LifetimeToken token = method();
            THEN("callback is not invoked")
            {
                CHECK(!called);
            }
        }

        WHEN("return value is discarded")
        {
            (void)method();
            THEN("callback is invoked")
            {
                CHECK(called);
            }
        }
    }

    GIVEN("a LifetimeToken with a callback")
    {
        util::LifetimeToken tokenA = util::LifetimeToken(callback);

        WHEN("LifetimeToken is moved")
        {
            util::LifetimeToken tokenB = std::move(tokenA);
            THEN("callback is not invoked")
            {
                CHECK(!called);
            }
        }

        WHEN("moved to token is expried")
        {
            {
                util::LifetimeToken tokenB = std::move(tokenA);
            }

            THEN("callback is invoked")
            {
                CHECK(called);
            }
        }

        WHEN("moved assigned callback is invoked")
        {
            auto tokenB = util::LifetimeToken();
            tokenA = std::move(tokenB);

            CHECK(called);
        }
    }
}

SCENARIO("LifetimeToken is valid when it has a callback")
{
    GIVEN("LifetimeToken is created with a callback")
    {
        auto token = util::LifetimeToken([]() {});

        THEN("token is valid")
        {
            CHECK(token);
        }

        WHEN("token is moved")
        {
            auto token2 = std::move(token);

            THEN("moved from token is invalid")
            {
                CHECK(!token);
            }

            THEN("moved to token is valid")
            {
                CHECK(token2);
            }
        }
    }

    GIVEN("LifetimeToken is created without a callback")
    {
        auto token = util::LifetimeToken();

        THEN("token is invalid")
        {
            CHECK(!token);
        }
    }
}

SCENARIO("LifetimeToken can be used with standard containers")
{
    THEN("LifetimeToken is move constructible")
    {
        CHECK(std::is_move_constructible<util::LifetimeToken>::value);
    }

    THEN("LifetimeToken is move assignable")
    {
        CHECK(std::is_move_constructible<util::LifetimeToken>::value);
    }
}
