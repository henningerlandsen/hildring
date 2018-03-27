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

    GIVEN("a System is added")
    {
        LifetimeStatus status{};
        auto result = ecs::Systems::addComponentSystem<LifetimeTracker>(status);

        THEN("the System is created")
        {
            CHECK(status.isCtorCalled);
        }

        THEN("result is true")
        {
            CHECK(result == true);
        }

        THEN("the System persists")
        {
            CHECK(!status.isDtorCalled);
        }

        THEN("the System is not copied")
        {
            CHECK(status.copyCount == 0);
        }

        WHEN("the same System is added again")
        {
            LifetimeStatus status2{};
            auto result2 = ecs::Systems::addComponentSystem<LifetimeTracker>(status2);

            THEN("the System is not created")
            {
                CHECK(false == status2.isCtorCalled);
            }

            THEN("result is false")
            {
                CHECK(false == result2);
            }
        }

        WHEN("Systems are reset")
        {
            ecs::Systems::reset();

            THEN("the System is destroyed")
            {
                CHECK(status.isDtorCalled);
            }
        }
        ecs::Systems::reset();
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
            auto actual = ecs::Systems::getSystem<MySystem>()->myValue;

            THEN("it has the initial values")
            {
                CHECK(42 == actual);
            }
        }

        WHEN("more systems are added")
        {
            struct OtherSystem {
            };

            auto expected = ecs::Systems::getSystem<MySystem>();
            ecs::Systems::addComponentSystem<OtherSystem>();
            THEN("earlier systems can be retrieved")
            {

                CHECK(expected == ecs::Systems::getSystem<MySystem>());
            }
        }

        WHEN("values are set")
        {
            ecs::Systems::getSystem<MySystem>()->myValue = 20;
            THEN("they remain the same")
            {
                CHECK(20 == ecs::Systems::getSystem<MySystem>()->myValue);
            }
        }
    }
}
