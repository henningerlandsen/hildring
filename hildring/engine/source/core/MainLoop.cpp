#include "core/MainLoop.h"

#include "events/Events.h"

namespace core {

int exitCode = -1;
bool doExit = false;

int MainLoop::run(std::chrono::milliseconds tickTime, std::chrono::steady_clock::time_point (*timeFunction)())
{
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
    }

    return exitCode;
}

void MainLoop::exit(int exitCode)
{
    core::exitCode = exitCode;
    doExit = true;
}
}
