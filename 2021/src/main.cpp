#include <iostream>

#define TESTING

void day01();
void day02();
void day03();
void day04();
void day05();
void day06();
void day07();
void day08();
void day09();
void day10();
void day11();
void day12();
void day13();
void day14();
void day15();
void day16();

int main(){
    std::cout << "Advent of Code 2021 solutions:" << std::endl;

#ifndef TESTING
    day01();
    day02();
    day03();
    day04();
    day05();
    day06();
    day07();
    day08();
    day09();
    day10();
    day11();
    day12();
    day13();
    day14();
    day15();
#endif
    day16();
}
