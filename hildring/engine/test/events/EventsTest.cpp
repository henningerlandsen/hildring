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
        Events::subscribe<int>(&object);

        WHEN("The event is fired")
        {
            auto eventData = 42;
            Events::dispatch(eventData);

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
            Events::dispatch(33);

            THEN("Subscribed method is called")
            {
                CHECK(object.isCalled);
                CHECK(object.data == 33);
            }
        }

        WHEN("Object unsubscribes")
        {
            Events::unsubscribe<int>(&object);

            WHEN("The event is dispatched")
            {
                Events::dispatch(25);

                THEN("Subcsribed method is not called")
                {
                    CHECK_FALSE(object.isCalled);
                }
            }
        }

        WHEN("Object subscribes twice")
        {
            Events::subscribe<int>(&object);

            WHEN("Event is dispatched")
            {
                Events::dispatch(-1);

                THEN("Object is only called once")
                {
                    CHECK(object.callCount == 1);
                }
            }
        }
    }
}
