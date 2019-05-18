#pragma once

#include <chrono>

namespace core {

struct TickEvent {
    std::chrono::milliseconds tickTime;
};

class MainLoop {
public:
    static int run(
        std::chrono::milliseconds tickTime,
        std::chrono::steady_clock::time_point (*timeFunction)() = &std::chrono::steady_clock::now,
        void (*sleepUntilFunction)(const std::chrono::steady_clock::time_point&) = nullptr);

    static void exit(int exitCode = 0);
};
}
