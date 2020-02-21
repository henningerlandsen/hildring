
macro(add_package)
    cmake_parse_arguments(PACKAGE "" "NAME" "SOURCES;TEST_SOURCES;DEPENDENCIES" ${ARGN})

    project(${PACKAGE_NAME} C CXX)

    message(STATUS "Package: ${PACKAGE_NAME}")
    message(STATUS "- Sources: ${PACKAGE_SOURCES}")
    message(STATUS "- Test Sources: ${PACKAGE_TEST_SOURCES}")
    message(STATUS "- Dependencies: ${PACKAGE_DEPENDENCIES}")

    if (PACKAGE_SOURCES)
        add_library(
            ${PACKAGE_NAME} 
            ${PACKAGE_SOURCES}
        )
        set(LIBRARY_TYPE PUBLIC)    
        set_property(TARGET ${PACKAGE_NAME} PROPERTY CXX_STANDARD 17)
    else()
        add_library(
            ${PACKAGE_NAME} 
            INTERFACE
        )
        set(LIBRARY_TYPE INTERFACE)
    endif()
    
    target_include_directories(
        ${PACKAGE_NAME}
        ${LIBRARY_TYPE}
        include/
    )

    if (PACKAGE_DEPENDENCIES)
        target_link_libraries(
            ${PACKAGE_NAME}
            ${LIBRARY_TYPE}
            ${PACKAGE_DEPENDENCIES}
        )
    endif()
 
    if (PACKAGE_TEST_SOURCES)
        set(TEST_TARGET ${PACKAGE_NAME}-test)

        add_executable(
            ${TEST_TARGET}
            ${CMAKE_MODULE_PATH}/test-main.cpp
            ${PACKAGE_TEST_SOURCES}
        )

        target_include_directories(
            ${TEST_TARGET}
            PRIVATE
            ../../ext/catch2
        )
        
        target_link_libraries(${TEST_TARGET} ${PACKAGE_NAME})

        add_test(
            NAME ${PACKAGE_NAME} 
            COMMAND ${TEST_TARGET}
        )

        set_property(TARGET ${TEST_TARGET} PROPERTY CXX_STANDARD 17)
    endif()

endmacro()
