cmake_minimum_required(VERSION 3.2)

project(AOC2022)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/day01.cpp
    # src/day02.cpp
    # src/day03.cpp
    # src/day04.cpp
    # src/day05.cpp
    # src/day06.cpp
)

set_property(TARGET ${PROJECT_NAME}
    PROPERTY CXX_STANDARD 20)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")