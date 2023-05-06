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

int main(int argc, char* argv[]){

    if (2 != argc) {
        std::cout << "Please specify the path to input files." << std::endl;
        return 0;
    }

    std::string path_prefix(argv[1]);
    std::string path;

    std::cout << "Advent of Code 2022 solutions:" << std::endl;

#ifndef TESTING
    path = path_prefix + "/day01.txt"; day01(path);
    path = path_prefix + "/day02.txt"; day02(path);
    // path = path_prefix + "/day03.txt"; day03(path);
    // path = path_prefix + "/day04.txt"; day04(path);
    // path = path_prefix + "/day05.txt"; day05(path);
    // path = path_prefix + "/day06.txt"; day06(path);
#endif
    
}
