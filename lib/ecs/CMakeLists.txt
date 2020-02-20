cmake_minimum_required(VERSION 3.8)

include(package)

package(NAME ecs
    SOURCES
    source/Entity.cpp
    TEST_SOURCES
    test/ComponentsTest.cpp
    test/EntityTest.cpp
    test/SystemsTest.cpp
    DEPENDENCIES
    util
    events
)

