cmake_minimum_required(VERSION 3.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)


add_subdirectory(hildring)
add_subdirectory(demo)

add_custom_target(tests COMMAND hildring-tests)
add_dependencies(tests hildring-tests)
