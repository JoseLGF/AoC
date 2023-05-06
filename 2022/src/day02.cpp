#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

#include "common.h"

int part_1(std::vector<std::string>& lines)
{
    std::vector<std::vector<int>> lookup = {
        {4, 8, 3}, {1, 5, 9}, {7, 2, 6}
    };
    int total_score = 0;

    for (auto line: lines) {
        int his  = line[0] - 'A';
        int mine = line[2] - 'X';

        total_score += lookup[his][mine];
    }

    return total_score;
}

int part_2(std::vector<std::string>& lines)
{
    std::vector<std::vector<int>> lookup = {
        {3, 4, 8}, {1, 5, 9}, {2, 6, 7}
    };
    int total_score = 0;

    for (auto line: lines) {
        int his  = line[0] - 'A';
        int mine = line[2] - 'X';

        total_score += lookup[his][mine];
    }

    return total_score;
}

void day02(std::string& input_path) {
    std::cout << "Day 2:" << std::endl;

    auto lines = get_input(input_path);
    std::cout << part_1(lines) << std::endl;
    std::cout << part_2(lines) << std::endl;
}
