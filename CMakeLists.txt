cmake_minimum_required(VERSION 3.5)

project(pwcard
    VERSION 0.0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARY_PUBLIC_HEADER
    include/pwcard/pwcard.h
)

set(LIBRARY_HEADERS
    include/linear_congruential_engine.h
    include/shuffle.h
    include/uniform_int_distribution.h
)

set(LIBRARY_SOURCES
    src/linear_congruential_engine.cpp
    src/pwcard.cpp
    src/uniform_int_distribution.cpp
)

add_library(${PROJECT_NAME} SHARED
    ${LIBRARY_PUBLIC_HEADER}
    ${LIBRARY_HEADERS}
    ${LIBRARY_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION       ${PROJECT_VERSION}
    SOVERSION     0
    PUBLIC_HEADER ${LIBRARY_PUBLIC_HEADER}
)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT lib
    PUBLIC_HEADER
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        COMPONENT dev
)
