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
        auto result = ecs::Systems::create<LifetimeTracker>(status);

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
            auto result2 = ecs::Systems::create<LifetimeTracker>(status2);

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
            ecs::Systems::create<CopyControl>(LifetimeTracker(status));

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

        ecs::Systems::create<MySystem>(42);

        THEN("it can be accessed")
        {
            CHECK(ecs::Systems::with<MySystem>([](MySystem&) {}));
        }

        WHEN("it is accessed")
        {
            THEN("accessor is invoked")
            {
                auto run = false;
                ecs::Systems::with<MySystem>([&run](MySystem&) {
                    run = true;
                });
                CHECK(run);
            }

            THEN("it has the initial values")
            {
                ecs::Systems::with<MySystem>([](MySystem& system) {
                    CHECK(42 == system.myValue);
                });
            }
        }

        WHEN("more systems are added")
        {
            struct OtherSystem {
            };

            ecs::Systems::create<OtherSystem>();
            THEN("earlier systems can be retrieved")
            {
                ecs::Systems::with<MySystem>([](MySystem& system) {
                    CHECK(42 == system.myValue);
                });
            }
        }

        WHEN("values are set")
        {
            ecs::Systems::with<MySystem>([](MySystem& system) {
                system.myValue = 20;
            });

            THEN("they remain the same")
            {
                ecs::Systems::with<MySystem>([](MySystem& system) {
                    CHECK(20 == system.myValue);
                });
            }
        }
    }

    GIVEN("A system is not added")
    {
        struct NoSystem {
        };

        WHEN("accessed")
        {
            THEN("accessor check fails")
            {
                CHECK(false == ecs::Systems::with<NoSystem>([](NoSystem&) {}));
            }

            THEN("accessor is not invoked")
            {
                auto run = false;
                ecs::Systems::with<NoSystem>([&run](NoSystem&) {
                    run = true;
                });
                CHECK(run == false);
            }
        }
    }
}
