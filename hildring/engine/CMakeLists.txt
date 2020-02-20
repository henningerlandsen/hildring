cmake_minimum_required(VERSION 3.8)

project(hildring C CXX)

find_package(OpenGL REQUIRED)

include_directories(
    include
    ../../ext/glfw/include
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

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)


target_link_libraries(${TEST_EXECUTABLE} ${PROJECT_NAME})

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ENABLE_COVERAGE)
    target_link_libraries(${PROJECT_NAME} debug --coverage)
    target_link_libraries(${TEST_EXECUTABLE} debug --coverage)
    include(CodeCoverage)
    set(EXCLUDE '*/hildring/externals/*' '*/hildring/engine/test/*' '/Applications/Xcode.app/*')
    setup_target_for_coverage(${PROJECT_NAME}-coverage ${TEST_EXECUTABLE} coverage "${EXCLUDE}") 
endif()
