#pragma once

#include <chrono>
#include <thread>

namespace threads {
class Loop {
public:
    Loop(std::chrono::milliseconds) {}

    std::thread::id threadId() const { return std::thread::id{}; }

private:
};
}
