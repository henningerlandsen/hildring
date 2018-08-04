cmake_minimum_required(VERSION 3.1)

project(hildring C CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

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

add_library(${PROJECT_NAME} ${SOURCES}) 

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw)

add_dependencies(${PROJECT_NAME} glfw)

# Tests
set(TEST_SOURCES
    test/main.cpp
    test/ecs/SystemsTest.cpp
    test/util/IndexTest.cpp
)

set(TEST_EXECUTABLE ${PROJECT_NAME}-tests)

add_executable(${TEST_EXECUTABLE} ${TEST_SOURCES})

target_include_directories(${TEST_EXECUTABLE} PRIVATE ../externals/catch2)

# Coverage
set(ENABLE_COVERAGE false CACHE BOOL "Enable code coverage target")

if(CMAKE_COMPILER_IS_GNUCXX AND ENABLE_COVERAGE)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}-coverage ${TEST_EXECUTABLE} coverage)
endif()


