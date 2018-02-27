#include "Window.h"

#include "GLFW/glfw3.h"

Window::Window(int width, int height, std::string title)
    : m_painter([] {})
{
    if (glfwInit()) {
        m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (m_window) {
            glfwMakeContextCurrent(m_window);
        } else {
            glfwTerminate();
        }
    }
}

Window::~Window()
{
    glfwTerminate();
}

void Window::setPainter(Painter p)
{
    m_painter = p;
}

bool Window::update()
{
    if (!glfwWindowShouldClose(m_window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        m_painter.paint();

        glfwSwapBuffers(m_window);

        glfwPollEvents();

        return true;
    }
    return false;
}
