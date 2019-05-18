#include "catch.hpp"

#include <chrono>

#include "core/MainLoop.h"
#include "events/Events.h"

using namespace std::chrono_literals;

std::chrono::steady_clock::time_point currentTime{};

std::chrono::steady_clock::time_point getTime()
{
    return currentTime;
}

void sleepUntil(const std::chrono::steady_clock::time_point& time)
{
    currentTime = time;
}

SCENARIO("Running a loop")
{
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
            auto exitCode = core::MainLoop::run(16ms, &getTime, &sleepUntil);

            THEN("It emits tick events")
            {
                CHECK(tickListener.gotTick);
            }

            THEN("Run returns the exit code")
            {
                CHECK(exitCode == 0);
            }

            THEN("It calls back at expected interval")
            {
                CHECK(tickListener.eventData.tickTime == 16ms);
            }

            THEN("It sleeps until next update")
            {
                CHECK(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()) == 32ms);
            }
        }
    }
}
