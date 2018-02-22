cmake_minimum_required(VERSION 3.1)

project(Demo C CXX)

include_directories(
    ../hildring/engine/include
)

add_compile_options(-std=c++14)

add_executable(Demo main.cpp)

target_link_libraries(Demo
    hildring
)

add_dependencies(Demo hildring)
