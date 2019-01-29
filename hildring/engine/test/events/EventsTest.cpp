#include "catch.hpp"

#include "events/Events.h"

SCENARIO("An object subscribes to an event")
{
    struct {
        void event(const int& eventData)
        {
            isCalled = true;
            data = eventData;
            callCount++;
        }
        bool isCalled = false;
        int data = 0;
        int callCount = 0;
    } object;

    GIVEN("An object with a subscription")
    {
        events::subscribe<int>(&object);

        WHEN("The event is fired")
        {
            auto eventData = 42;
            events::dispatch(eventData);

            THEN("Subscribed method is called")
            {
                CHECK(object.isCalled);
            }

            THEN("Event data is passed")
            {
                CHECK(object.data == 42);
            }
        }

        WHEN("Event is dispatched using r-value")
        {
            events::dispatch(33);

            THEN("Subscribed method is called")
            {
                CHECK(object.isCalled);
                CHECK(object.data == 33);
            }
        }

        WHEN("Object unsubscribes")
        {
            events::unsubscribe<int>(&object);

            WHEN("The event is dispatched")
            {
                events::dispatch(25);

                THEN("Subcsribed method is not called")
                {
                    CHECK_FALSE(object.isCalled);
                }
            }
        }

        WHEN("Object subscribes twice")
        {
            events::subscribe<int>(&object);

            WHEN("Event is dispatched")
            {
                events::dispatch(-1);

                THEN("Object is only called once")
                {
                    CHECK(object.callCount == 1);
                }
            }
        }
    }
}

SCENARIO("An event subscription is bound to scope")
{
    GIVEN("A class that subscibes to an event")
    {
        struct Listener {
            Listener()
            {
                eventToken = events::subscription<int>(this);
            }

            void event(const int&) { FAIL(); }

            util::LifetimeToken eventToken;
        };

        WHEN("Instance is created and destroyed")
        {
            {
                auto l = Listener{};
            }

            THEN("Triggering event does not crash")
            {
                REQUIRE_NOTHROW(events::dispatch(100));
            }
        }
    }
}
