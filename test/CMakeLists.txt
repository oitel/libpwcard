cmake_minimum_required(VERSION 3.5)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(pwcard_test
    main.cpp
    test_convert.cpp
    test_generate.cpp
)

target_link_libraries(pwcard_test
    PRIVATE
        pwcard
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")
include(Catch)
catch_discover_tests(pwcard_test)
