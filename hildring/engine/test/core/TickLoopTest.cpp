#include "catch.hpp"

#include <chrono>
#include <thread>

#include "core/TickLoop.h"

SCENARIO("Running a loop")
{
    WHEN("A loop is created")
    {
        auto loop = threads::Loop{ std::chrono::milliseconds(1) };

        THEN("It's id is valid")
        {
            CHECK(loop.threadId() != std::thread::id{});
        }

        THEN("It's id is different from the main thread")
        {
            CHECK(loop.threadId() != std::this_thread::get_id());
        }
    }
}
