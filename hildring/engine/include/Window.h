#pragma once

#include <string>

class GLFWwindow;

class Window {
public:
    Window(int width, int height, std::string title);
    ~Window();

    bool update();

private:
    GLFWwindow* windowHandle;
};
