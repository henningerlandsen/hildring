#include "catch.hpp"

#include <chrono>
#include <future>

#include "core/TickLoop.h"
#include "events/Events.h"

SCENARIO("Running a loop")
{
    GIVEN("A loop is created")
    {
        auto loop = core::TickLoop{ std::chrono::milliseconds(1) };

        WHEN("Running the loop")
        {
            loop.run();

            THEN("It emits tick events")
            {
                struct {
                    void event(const core::TickEvent& event)
                    {
                        promise.set_value(event.tickTime);
                    }
                    std::promise<std::chrono::milliseconds> promise;
                } tickListener;

                auto token = events::subscription<core::TickEvent>(&tickListener);
                auto future = tickListener.promise.get_future();
                future.wait_for(std::chrono::microseconds(10));

                CHECK(future.valid());
            }
        }
    }
}
