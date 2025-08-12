#include <memory>
#include <string>

#include "Engine.h"

#include "GLFW/glfw3.h"

struct Shader {
	Shader(std::string vertex, std::string fragment)
	: vertex_id(glCreateShader(GL_VERTEX_SHADER))
    , fragment_id(glCreateShader(GL_FRAGMENT_SHADER)) {
        const char* program[1] = { vertex.c_str() };
        glShaderSource(vertex_id, 1, program, nullptr);
        glCompileShader(vertex_id);
        program[1] = fragment.c_str();
        glShaderSource(fragment_id, 1, program, nullptr);
        glCompileShader(fragment_id);
	}

    const GLuint vertex_id;
    const GLuint fragment_id;
};


int main(int argc, char** argv)
{
    std::unique_ptr<Shader> shader;
    std::string fragment = R"(#version 300 es
precision mediump float;

out vec4 fragColor;

void main()
{
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
    )";

    std::string vertex = R"(#version 300 es

in vec4 vert;

void main()
{
    gl_Position = vert;
}
)";


    Engine eng([&shader, fragment, vertex] {
        if (!shader) {
	        shader = std::make_unique<Shader>(vertex, fragment);
        }
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
