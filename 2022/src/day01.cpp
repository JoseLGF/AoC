#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

int day01_1(std::string& input_path) {
    std::ifstream infile(input_path);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(infile, line))
    {
        lines.push_back(line);
    }

    int max = 0;
    int current = 0;
    for (auto line: lines) {
        if (line.empty()) {
            if (current > max) {
                max = current;
            }
            current = 0;
        }
        else {
            int calories = std::stoi(line);
            current += calories;
        }
    }
    return max;
}

void day01(std::string& input_path) {
    std::cout << "Day 1:" << std::endl;
    std::cout << day01_1(input_path) << std::endl;
}
