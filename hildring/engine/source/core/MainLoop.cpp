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

    if (!sleepUntil) {
        sleepUntil = &std::this_thread::sleep_until<std::chrono::steady_clock, std::chrono::steady_clock::duration>;
    }
    auto lastTick = time();
    auto nextTick = lastTick;
    while (!doExit) {
        const auto currentTime = time();
        do {
            nextTick += tickTime;
        } while (nextTick < currentTime);
        const auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(nextTick - lastTick);
        lastTick = nextTick;
        events::dispatch(TickEvent{ deltaTime });
        sleepUntil(nextTick);
    }

    return exitCode;
}

void MainLoop::exit(int withCode)
{
    exitCode = withCode;
    doExit = true;
}
}
