#include "util/LifetimeTokenStack.h"

#include "catch.hpp"

SCENARIO("Tokens can be pushed on the stack")
{
    GIVEN("An existing token")
    {
        auto tokenStack = util::LifetimeTokenStack{};
        auto tokenInvoked = false;
        auto token = util::LifetimeToken{
            [&tokenInvoked]() {
                tokenInvoked = true;
            }
        };
        WHEN("The token is pushed on the stack")
        {
            tokenStack.push(std::move(token));
            THEN("The token is not invoked")
            {
                CHECK_FALSE(tokenInvoked);
            }

            THEN("The token is invalidated")
            {
                CHECK_FALSE(token);
            }
        }
    }
}

SCENARIO("It invokes the tokens when stack is cleared")
{
    GIVEN("A LifetimeTokenStack with two tokens")
    {
        auto destroyCount = 0u;
        auto tokenStack = util::LifetimeTokenStack{};
        auto callback = [&destroyCount]() {
            destroyCount++;
        };
        tokenStack.push(util::LifetimeToken(callback));
        tokenStack.push(util::LifetimeToken(callback));

        WHEN("the stack is cleared")
        {
            tokenStack = util::LifetimeTokenStack{};
            THEN("the second token is destroyed first")
            {
                CHECK(destroyCount == 2);
            }
        }
    }
}
