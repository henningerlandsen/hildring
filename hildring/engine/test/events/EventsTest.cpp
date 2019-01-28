#include "catch.hpp"

#include "events/Events.h"

SCENARIO("An object subscribes to an event")
{
    struct {
        void event(const int& eventData)
        {
            isCalled = true;
            data = eventData;
        }
        bool isCalled = false;
        int data = 0;
    } object;

    GIVEN("An object with a subscription")
    {
        Events::subscribe<int>(&object);

        WHEN("The event is fired")
        {
            auto eventData = 42;
            Events::dispatch<int>(eventData);

            THEN("Subscribed method is called")
            {
                CHECK(object.isCalled);
            }

            THEN("Event data is passed")
            {
                CHECK(object.data == 42);
            }
        }
    }
}
