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

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-std=c++14 -Wall -Wextra -Werror)
endif()

add_library(hildring ${SOURCES}) 

target_link_libraries(hildring ${OPENGL_LIBRARIES} glfw)

add_dependencies(hildring glfw)

# Tests
set(TEST_SOURCES
    test/main.cpp
    test/ecs/SystemsTest.cpp
    test/util/IndexTest.cpp
)

add_executable(hildring-tests ${TEST_SOURCES})

target_include_directories(hildring-tests PRIVATE ../externals/catch2)


