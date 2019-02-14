#pragma once

#include <chrono>
#include <thread>

namespace core {

struct TickEvent {
    std::chrono::milliseconds tickTime;
};

class TickLoop {
public:
    TickLoop(std::chrono::milliseconds) {}

    void run() {}

    void stop() {}

private:
};
}
