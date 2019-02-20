#include "catch.hpp"

#include <chrono>

#include "core/MainLoop.h"
#include "events/Events.h"

using namespace std::chrono_literals;

std::chrono::steady_clock::time_point startTime{};
std::chrono::steady_clock::duration increment{};
unsigned int getTimeCallCount{ 0u };

std::chrono::steady_clock::time_point getTime()
{
    getTimeCallCount++;
    return startTime += increment;
}

SCENARIO("Running a loop")
{
    getTimeCallCount = 0u;

    GIVEN("A tick event listener")
    {
        struct {
            void event(const core::TickEvent& e)
            {
                if (!gotTick) {
                    gotTick = true;
                } else {
                    core::MainLoop::exit(0);
                }
                eventData = e;
            }
            bool gotTick{ false };
            core::TickEvent eventData;
        } tickListener;

        auto token = events::subscription<core::TickEvent>(&tickListener);

        WHEN("Running the main loop")
        {
            increment = 2ms;
            auto exitCode = core::MainLoop::run(16ms, &getTime);

            THEN("It emits tick events")
            {
                CHECK(tickListener.gotTick);
            }

            THEN("Run returns the exit code")
            {
                CHECK(exitCode == 0);
            }

            THEN("It checks the time")
            {
                CHECK(getTimeCallCount != 0);
            }

            THEN("It calls back at expected interval")
            {
                CHECK(tickListener.eventData.tickTime == 16ms);
            }
        }
    }
}
