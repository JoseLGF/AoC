cmake_minimum_required(VERSION 3.2)

project(AOC2021)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/day01.cpp
    src/day02.cpp
    src/day03.cpp
    src/day04.cpp
    src/day05.cpp
    src/day06.cpp
    src/day07.cpp
    src/day08.cpp
    src/day09.cpp
    src/day10.cpp
    src/day11.cpp
    src/day12.cpp
    src/day13.cpp
    src/day14.cpp
    src/day15.cpp
    src/day16.cpp
    src/day17.cpp
    src/day18.cpp
)

set_property(TARGET ${PROJECT_NAME}
    PROPERTY CXX_STANDARD 20)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")