add_executable (AoC2024 "AoC2024.cpp" "AoC2024.h"  "common.h" "common.cpp"  "day05.cpp" "day05.h" "day04.h" "day04.cpp" "day03.h" "day03.cpp" "day02.h" "day02.cpp" "day01.h" "day01.cpp" "day06.h" "day06.cpp" "day07.h" "day07.cpp" "day08.h" "day08.cpp" "day09.h" "day09.cpp" "Day10.h" "Day10.cpp" "day11.h" "day11.cpp" "day12.h" "Day12.cpp"  "day13.h" "day13.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AoC2024 PROPERTY CXX_STANDARD 20)
endif()
