#include "Engine.h"

#include "GLFW/glfw3.h"

int main(int argc, char** argv)
{
    Engine eng([] {
        glBegin(GL_QUADS);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glEnd();
    });

    return eng.run();
}
