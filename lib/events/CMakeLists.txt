cmake_minimum_required(VERSION 3.8)

include(package)

add_package(NAME events
    TEST_SOURCES
    test/EventsTest.cpp
    DEPENDENCIES
    util
)

