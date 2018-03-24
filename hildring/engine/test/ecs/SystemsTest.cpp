#include "catch.hpp"
#include <iostream>

#include "ecs/Systems.h"

SCENARIO("Adding Systems")
{
    struct LifetimeStatus {
    public:
        bool isCtorCalled = false;
        bool isDtorCalled = false;
        int copyCount = 0;
    };
    class LifetimeTracker {
    public:
        explicit LifetimeTracker(LifetimeStatus& _status)
            : status(_status)
        {
            status.isCtorCalled = true;
        }

        LifetimeTracker(const LifetimeTracker& rhs) noexcept
            : status(rhs.status)
        {
            status.copyCount += 1;
        }

        LifetimeTracker(LifetimeTracker&& rhs) noexcept
            : status(rhs.status)
        {
        }

        ~LifetimeTracker()
        {
            status.isDtorCalled = true;
        }

    private:
        LifetimeStatus& status;
    };

    WHEN("a System is added")
    {
        LifetimeStatus status{};
        ecs::Systems::addComponentSystem<LifetimeTracker>(status);

        THEN("the System is created")
        {
            CHECK(status.isCtorCalled);
        }

        THEN("the System persists")
        {
            CHECK(!status.isDtorCalled);
        }

        THEN("the System is not copied")
        {
            CHECK(status.copyCount == 0);
        }
    }

    GIVEN("arguments are passed")
    {
        class CopyControl {
        public:
            explicit CopyControl(LifetimeTracker _tracker)
                : tracker(std::move(_tracker))
            {
            }

        private:
            LifetimeTracker tracker;
        };

        WHEN("a system is added")
        {
            LifetimeStatus status{};
            ecs::Systems::addComponentSystem<CopyControl>(LifetimeTracker(status));

            THEN("arguments are not copied")
            {
                CHECK(status.copyCount == 0);
            }
        }
    }

    GIVEN("a system is added")
    {
        struct MySystem {
            MySystem() {}
            MySystem(int value)
                : myValue(value)
            {
            }

            int myValue = 0;
        };

        ecs::Systems::addComponentSystem<MySystem>(42);
        WHEN("it is retrieved")
        {
            THEN("it has the initial values")
            {
                auto actual = ecs::Systems::getSystem<MySystem>().myValue;
                CHECK(42 == actual);
            }
        }
        WHEN("values are set")
        {
            THEN("they remain the same")
            {
            }
        }
    }
}
