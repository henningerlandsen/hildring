cmake_minimum_required(VERSION 3.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(hildring)
add_subdirectory(demo)

add_custom_target(tests COMMAND hildring-tests)
add_dependencies(tests hildring-tests)
