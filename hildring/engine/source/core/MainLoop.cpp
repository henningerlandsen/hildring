#include "core/MainLoop.h"

namespace core {
int MainLoop::run(std::chrono::milliseconds)
{
    return 1;
}

void MainLoop::exit(int)
{
}
}
