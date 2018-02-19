cmake_minimum_required(VERSION 3.1)

find_package(OpenGL REQUIRED)

project(Demo)

include_directories(
    ../hildring/externals/glfw/include
    ${OPENGL_INCLUDE_DIRS}
)

add_executable(Demo main.cpp)

target_link_libraries(Demo
    ${OPENGL_LIBRARIES}
    glfw
)

add_dependencies(Demo glfw)
