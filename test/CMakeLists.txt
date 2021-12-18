cmake_minimum_required(VERSION 3.5)

add_executable(pwcard_test
    main.cpp
    test_convert.cpp
    test_generate.cpp
)

find_package(Catch2 REQUIRED)
target_link_libraries(pwcard_test
    PRIVATE
        Catch2::Catch2
        pwcard
)

include(Catch)
catch_discover_tests(pwcard_test)
