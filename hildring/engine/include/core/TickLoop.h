#pragma once

#include <chrono>
#include <thread>

namespace core {

struct TickEvent {
    std::chrono::milliseconds tickTime;
};

class MainLoop {
public:
    static int run(std::chrono::milliseconds) { return 1; }

    static void exit(int exitCode = 0){};
};
}
