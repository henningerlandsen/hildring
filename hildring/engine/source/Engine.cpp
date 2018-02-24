#include "Engine.h"
#include <chrono>
#include <thread>

Engine::Engine(int windowWidth, int windowHeight)
    : window(windowWidth, windowHeight, "Hildring Engine")
{
}

int Engine::run()
{
    using namespace std::literals::chrono_literals;

    while (window.update()) {
        std::this_thread::sleep_for(16ms);
    }
    return 0;
}
