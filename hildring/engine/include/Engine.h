#pragma once

#include <functional>

#include "Window.h"

class Engine {
public:
    Engine(std::function<void()> drawFunc);

    int run();

private:
    Window window;
};
