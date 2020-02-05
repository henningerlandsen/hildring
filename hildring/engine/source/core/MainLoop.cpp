#include "core/MainLoop.h"

#include "events/Events.h"

#include <thread>

namespace core {

int exitCode = -1;
bool doExit = false;

int MainLoop::run(
    std::chrono::milliseconds tickTime,
    std::chrono::steady_clock::time_point (*time)(),
    void (*sleepUntil)(const std::chrono::steady_clock::time_point&))
{
    doExit = false;

    if (!sleepUntil) {
        sleepUntil = &std::this_thread::sleep_until<std::chrono::steady_clock, std::chrono::steady_clock::duration>;
    }

    auto timeToTick = time();
    while (!doExit) {
        const auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(time() - timeToTick);
        if (deltaTime > tickTime)
            timeToTick = time();
        else {
            timeToTick += tickTime;
        }
        events::dispatch(TickEvent{ deltaTime });
        sleepUntil(timeToTick);
    }

    return exitCode;
}

void MainLoop::exit(int withCode)
{
    exitCode = withCode;
    doExit = true;
}
}
