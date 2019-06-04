#include "catch.hpp"

#include <chrono>

#include "core/MainLoop.h"
#include "events/Events.h"

#define DURATION_EQ(d1, d2) CHECK((d1).count() == (d2).count())

using namespace std::chrono_literals;

std::chrono::steady_clock::time_point currentTime{};

std::chrono::steady_clock::time_point getTime()
{
    return currentTime;
}

void sleepUntil(const std::chrono::steady_clock::time_point& time)
{
    if (currentTime < time) {
        currentTime = time;
    }
}

SCENARIO("Running a loop")
{
    currentTime = std::chrono::steady_clock::time_point{};
    struct {
        void event(const core::TickEvent& e)
        {
            eventData = e;
            currentTime += tickTime;
            if (++tickCount == recordForTicks) {
                core::MainLoop::exit(exitCode);
            }
        }

        unsigned int tickCount{ 0u };
        unsigned int recordForTicks{ 1u };
        int exitCode{ 0 };
        std::chrono::steady_clock::duration tickTime{};
        core::TickEvent eventData;
    } tickHandler;

    auto token = events::subscription<core::TickEvent>(&tickHandler);

    GIVEN("One tick is recorded")
    {
        tickHandler.exitCode = 555;

        WHEN("Running the main loop")
        {
            auto exitCode = core::MainLoop::run(16ms, &getTime, &sleepUntil);

            THEN("It records one tick event")
            {
                CHECK(tickHandler.tickCount == 1);
            }

            THEN("Run returns the expected code")
            {
                CHECK(exitCode == 555);
            }

            THEN("The first tick is immideately")
            {
                DURATION_EQ(tickHandler.eventData.tickTime, 0ms);
            }
        }
    }

    GIVEN("Multiple ticks are recorded")
    {
        tickHandler.recordForTicks = 10u;

        WHEN("Running the main loop")
        {
            auto exitCode = core::MainLoop::run(16ms, &getTime, &sleepUntil);

            THEN("Expected number of ticks are recorded")
            {
                CHECK(tickHandler.tickCount == 10);
            }

            THEN("Time has advanced when exiting")
            {
                const auto timeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch());
                DURATION_EQ(timeSinceStart, 160ms);
                }
        }
    }

    GIVEN("Tick loop is stalled")
    {
        tickHandler.recordForTicks = 5u;
        tickHandler.tickTime = 30ms;

        WHEN("Running the main loop")
        {
            auto exitCode = core::MainLoop::run(10ms, &getTime, &sleepUntil);

            THEN("Time has advanced as expected")
            {
                const auto timeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch());
                DURATION_EQ(timeSinceStart, 150ms);
            }

            THEN("Delay is reflected in tick time")
            {
                DURATION_EQ(tickHandler.eventData.tickTime, 30ms);
            }
        }
    }
}
