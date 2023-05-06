#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

int day01_1(std::vector<std::string>& lines) {
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

int day01_2(std::vector<std::string>& lines) {
    std::vector<int> calories_counts;
    int current = 0;

    for (auto line: lines) {
        if (line.empty()) {
            calories_counts.push_back(current);
            current = 0;
        }
        else {
            int calories = std::stoi(line);
            current += calories;
        }
    }

    std::sort(calories_counts.begin(),
              calories_counts.end(),
              std::greater<int>());

    return  calories_counts[0] +
            calories_counts[1] +
            calories_counts[2];
}

void day01(std::string& input_path) {
    std::cout << "Day 1:" << std::endl;

    std::ifstream infile(input_path);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(infile, line))
    {
        lines.push_back(line);
    }

    std::cout << day01_1(lines) << std::endl;
    std::cout << day01_2(lines) << std::endl;
}
