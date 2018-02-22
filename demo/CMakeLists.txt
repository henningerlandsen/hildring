cmake_minimum_required(VERSION 3.10)

project(Demo)

include_directories(
    ../hildring/engine/include
)

add_executable(Demo main.cpp)

target_link_libraries(Demo
    hildring
)

add_dependencies(Demo hildring)
