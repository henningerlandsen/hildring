#pragma once

#include <functional>

class Painter {
public:
    Painter(std::function<void()> paintFunc);

    void paint();

private:
    std::function<void()> m_paintFunc;
};
