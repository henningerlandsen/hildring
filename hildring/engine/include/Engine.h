#pragma once

#include "Window.h"

class Engine {
public:
    Engine(int windowWidth, int windowHeight);

    int run();

private:
    Window window;
};
