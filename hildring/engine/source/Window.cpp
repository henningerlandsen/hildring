#include "Window.h"

#include "GLFW/glfw3.h"

Window::Window(int width, int height, std::string title) 
{
    if (glfwInit()) 
    {
        windowHandle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (windowHandle)
        {
            glfwMakeContextCurrent(windowHandle);
        } 
        else 
        {
            glfwTerminate();
        }
    }
}

Window::~Window() 
{
    glfwTerminate();
}


bool Window::update() 
{
    if (!glfwWindowShouldClose(windowHandle)) 
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(windowHandle);

        /* Poll for and process events */
        glfwPollEvents();

        return true;
    }
    return false;
}
