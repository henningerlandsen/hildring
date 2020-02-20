cmake_minimum_required(VERSION 3.8)

include(package)

package(NAME core
    SOURCES
    source/MainLoop.cpp
    TEST_SOURCES
    test/MainLoopTest.cpp
    DEPENDENCIES
    events
)

