#pragma once

#include <string>

#include "Painter.h"

struct GLFWwindow;

class Window {
public:
    Window(int width, int height, std::string title);
    ~Window();

    bool update();

    void setPainter(Painter p);

private:
    GLFWwindow* m_window;
    Painter m_painter;
};
