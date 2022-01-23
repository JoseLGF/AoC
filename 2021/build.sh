g++ -c -g src/day01.cpp
g++ -c -g src/day02.cpp
g++ -c -g src/day03.cpp
g++ -c -g src/main.cpp
g++ *.o -o aoc2021

# Clean
rm *.o
