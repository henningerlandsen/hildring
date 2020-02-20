cmake_minimum_required(VERSION 3.8)

include(package)

package(NAME util
    SOURCES
    source/LifetimeToken.cpp
    source/LifetimeTokenStack.cpp
    TEST_SOURCES
    test/IndexTest.cpp
    test/LifetimeTokenStackTest.cpp
    test/LifetimeTokenTest.cpp
)

