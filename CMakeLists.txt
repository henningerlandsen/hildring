cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

enable_testing()

#add_subdirectory(hildring)
#add_subdirectory(app/demo)

# External dependencies
#add_subdirectory(ext/glfw)

# Internal packages
add_subdirectory(lib/util)
add_subdirectory(lib/events)
add_subdirectory(lib/core)
add_subdirectory(lib/ecs)
