cmake_minimum_required(VERSION 3.1)

project(hildring C CXX)

find_package(OpenGL REQUIRED)

include_directories(
    include
    ../externals/glfw/include
    ${OPENGL_INCLUDE_DIRS}
)

set(SOURCES
    source/Engine.cpp
    source/Painter.cpp
    source/Window.cpp
)

add_compile_options(-std=c++14)

add_library(hildring ${SOURCES})

target_link_libraries(hildring ${OPENGL_LIBRARIES} glfw)

add_dependencies(hildring glfw)
