cmake_minimum_required(VERSION 3.8)

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

    source/core/MainLoop.cpp
    source/ecs/Entity.cpp
    source/util/LifetimeToken.cpp
    source/util/LifetimeTokenStack.cpp
)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)

    # Coverage
    set(ENABLE_COVERAGE false CACHE BOOL "Enable code coverage target")

    if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ENABLE_COVERAGE)
        add_compile_options(-g -O0 -fprofile-arcs -ftest-coverage)
   endif()
endif()

add_library(${PROJECT_NAME} ${SOURCES}) 

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw)

add_dependencies(${PROJECT_NAME} glfw)

# Tests
set(TEST_SOURCES
    test/main.cpp
    test/core/MainLoopTest.cpp
    test/ecs/ComponentsTest.cpp
    test/ecs/EntityTest.cpp
    test/ecs/SystemsTest.cpp
    test/events/EventsTest.cpp
    test/util/IndexTest.cpp
    test/util/LifetimeTokenTest.cpp
    test/util/LifetimeTokenStackTest.cpp
)

set(TEST_EXECUTABLE ${PROJECT_NAME}-tests)

add_executable(${TEST_EXECUTABLE} ${TEST_SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${TEST_EXECUTABLE} PROPERTY CXX_STANDARD 17)

target_include_directories(${TEST_EXECUTABLE} PRIVATE ../externals/catch2)

target_link_libraries(${TEST_EXECUTABLE} ${PROJECT_NAME})

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ENABLE_COVERAGE)
    target_link_libraries(${PROJECT_NAME} debug --coverage)
    target_link_libraries(${TEST_EXECUTABLE} debug --coverage)
    include(CodeCoverage)
    set(EXCLUDE '*/hildring/externals/*' '*/hildring/engine/test/*' '/Applications/Xcode.app/*')
    setup_target_for_coverage(${PROJECT_NAME}-coverage ${TEST_EXECUTABLE} coverage "${EXCLUDE}") 
endif()
