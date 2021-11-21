cmake_minimum_required(VERSION 3.5)

project(pwcard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pwcard
    main.cpp
    pwcard.h pwcard.cpp

    linear_congruential_engine.h linear_congruential_engine.cpp
    uniform_int_distribution.h uniform_int_distribution.cpp
    shuffle.h
)
