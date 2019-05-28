#include "core/MainLoop.h"

#include "events/Events.h"

#include <thread>

namespace core {

int exitCode = -1;
bool doExit = false;

int MainLoop::run(
    std::chrono::milliseconds tickTime,
    std::chrono::steady_clock::time_point (*timeFunction)(),
    void (*sleepUntilFunction)(const std::chrono::steady_clock::time_point&))
{

    if (!sleepUntilFunction) {
        sleepUntilFunction = &std::this_thread::sleep_until<std::chrono::steady_clock, std::chrono::steady_clock::duration>;
    }
    auto lastUpdate = timeFunction();
    auto nextUpdate = lastUpdate;
    while (!doExit) {
        const auto currentTime = timeFunction();
        do {
            nextUpdate += tickTime;
        } while (nextUpdate < currentTime);
        const auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(nextUpdate - lastUpdate);
        lastUpdate = nextUpdate;
        events::dispatch(TickEvent{ deltaTime });
        sleepUntilFunction(nextUpdate);
    }

    return exitCode;
}

void MainLoop::exit(int withCode)
{
    exitCode = withCode;
    doExit = true;
}
}
