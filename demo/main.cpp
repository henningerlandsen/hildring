#include "Window.h"

#include <chrono>
#include <thread>

using namespace std::literals::chrono_literals;

int main(int argc, char** argv)
{
    Window window(640, 480, "Hello, World!");

    while (window.update()) {
        std::this_thread::sleep_for(16ms);
    }

    return 0;
}
