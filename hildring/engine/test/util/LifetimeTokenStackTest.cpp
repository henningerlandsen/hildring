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

SCENARIO("It invokes tokens in the reverse order of creation")
{
    GIVEN("A LifetimeTokenStack with two tokens")
    {
        std::vector<int> destroyOrder;
        auto tokenStack = util::LifetimeTokenStack{};
        tokenStack.push(util::LifetimeToken([&destroyOrder]() {
            destroyOrder.push_back(2);
        }));
        tokenStack.push(util::LifetimeToken([&destroyOrder]() {
            destroyOrder.push_back(1);
        }));

        WHEN("the stack is cleared")
        {
            tokenStack = util::LifetimeTokenStack{};
            THEN("the second token is destroyed first")
            {
                CHECK(destroyOrder[0] == 1);
                CHECK(destroyOrder[1] == 2);
            }
        }
    }

    GIVEN("A vector of tokens")
    {
        bool one = false, two = false;
        std::vector<util::LifetimeToken> tokens;
        tokens.emplace_back([&one]() { one = true; });
        tokens.emplace_back([&two]() { two = true; });

        tokens.pop_back();

        CHECK(two == true);
        CHECK(one == false);
    }
}
