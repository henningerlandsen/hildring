#include "catch.hpp"

#include <chrono>

#include "core/TickLoop.h"
#include "events/Events.h"

SCENARIO("Running a loop")
{

    GIVEN("A tick event listener")
    {
        struct {
            void event(const core::TickEvent&)
            {
                gotTick = true;
                core::MainLoop::exit(0);
            }
            bool gotTick{ false };
        } tickListener;

        auto token = events::subscription<core::TickEvent>(&tickListener);

        WHEN("Running the main loop")
        {
            auto exit_code = core::MainLoop::run(std::chrono::milliseconds(1));

            THEN("It emits tick events")
            {
                CHECK(tickListener.gotTick);
            }

            THEN("Run returns the exit code")
            {
                CHECK(exit_code == 0);
            }
        }
    }
}
