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
    source/ecs/Systems.cpp
)

set(HEADERS
    include/ecs/Systems.h
)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-std=c++14 -Wall -Wextra -Werror)
endif()

add_library(hildring ${SOURCES} ${HEADERS})

target_link_libraries(hildring ${OPENGL_LIBRARIES} glfw)

add_dependencies(hildring glfw)

# Tests
set(TEST_SOURCES
    test/main.cpp
    test/ecs/SystemsTest.cpp
)

include_directories(
    ../externals/catch2
)

add_executable(hildring-tests ${TEST_SOURCES})
