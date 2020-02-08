cmake_minimum_required(VERSION 3.1)

project(hildring-root)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(hildring)
add_subdirectory(demo)

# External dependencies
add_subdirectory(ext/glfw)


add_custom_target(tests COMMAND hildring-tests)
add_dependencies(tests hildring-tests)
