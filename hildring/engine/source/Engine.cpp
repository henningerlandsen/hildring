#include "Engine.h"
#include <chrono>
#include <thread>

Engine::Engine(std::function<void()> drawFunc)
    : window(640, 480, "Hildring Engine")
{
    window.setPainter(Painter(drawFunc));
}

int Engine::run()
{
    using namespace std::literals::chrono_literals;

    while (window.update()) {
        std::this_thread::sleep_for(16ms);
    }
    return 0;
}
