cmake_minimum_required(VERSION 3.5)

add_executable(pwcard_example
    main.cpp
)

target_link_libraries(pwcard_example
    PRIVATE
        pwcard
)

set_target_properties(pwcard_example PROPERTIES
    OUTPUT_NAME pwcard
)
