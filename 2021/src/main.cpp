#include <iostream>
#include <fstream>
#include <string>

// #define TESTING
void day01(std::string& input_path);
void day02(std::string& input_path);
void day03(std::string& input_path);
void day04(std::string& input_path);
void day05(std::string& input_path);
void day06(std::string& input_path);
void day07(std::string& input_path);
void day08(std::string& input_path);
void day09(std::string& input_path);
void day10(std::string& input_path);
void day11(std::string& input_path);
void day12(std::string& input_path);
void day13(std::string& input_path);
void day14(std::string& input_path);
void day15(std::string& input_path);
void day16(std::string& input_path);
void day17(std::string& input_path);
void day18(std::string& input_path);

int main(int argc, char* argv[]){

    if (2 != argc) {
        std::cout << "Please specify the path to input files." << std::endl;
        return 0;
    }

    std::string path_prefix(argv[1]);
    std::string path;

    std::cout << "Advent of Code 2021 solutions:" << std::endl;

#ifndef TESTING
    path = path_prefix + "/day01.txt"; day01(path);
    path = path_prefix + "/day02.txt"; day02(path);
    path = path_prefix + "/day03.txt"; day03(path);
    path = path_prefix + "/day04.txt"; day04(path);
    path = path_prefix + "/day05.txt"; day05(path);
    path = path_prefix + "/day06.txt"; day06(path);
    path = path_prefix + "/day07.txt"; day07(path);
    path = path_prefix + "/day08.txt"; day08(path);
    path = path_prefix + "/day09.txt"; day09(path);
    path = path_prefix + "/day10.txt"; day10(path);
    path = path_prefix + "/day11.txt"; day11(path);
    path = path_prefix + "/day12.txt"; day12(path);
    path = path_prefix + "/day13.txt"; day13(path);
    path = path_prefix + "/day14.txt"; day14(path);
    path = path_prefix + "/day15.txt"; day15(path);
    path = path_prefix + "/day16.txt"; day16(path);
    path = path_prefix + "/day17.txt"; day17(path);
#endif
    path = "input/day18.txt"; day18(path);
}
