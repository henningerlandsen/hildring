#include "core/MainLoop.h"

#include "events/Events.h"

namespace core {

int exitCode = -1;
bool doExit = false;

int MainLoop::run(std::chrono::milliseconds)
{
    while (!doExit) {
        events::dispatch(TickEvent{});
    }

    return exitCode;
}

void MainLoop::exit(int exitCode)
{
    core::exitCode = exitCode;
    doExit = true;
}
}
