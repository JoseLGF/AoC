#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <limits>

void day09()
{
    std::ifstream infile("input/day09.txt");

    // Parse data
    std::string line;
    std::string token;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    // Part 1 - Find low points
    int height = lines.size();
    int width = lines[0].size();
    int sum_of_risks = 0;
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            bool left_is_higher = false;
            bool right_is_higher = false;
            bool up_is_higher = false;
            bool down_is_higher = false;

            if ( (0 == x) || (lines[y][x-1] > lines[y][x])) {
                left_is_higher = true;
            }
            if ( (width-1 == x) || (lines[y][x+1] > lines[y][x])) {
                right_is_higher = true;
            }
            if ( (0 == y) || (lines[y-1][x] > lines[y][x])) {
                up_is_higher = true;
            }
            if ( (height-1 == y) || (lines[y+1][x] > lines[y][x])) {
                down_is_higher = true;
            }

            if (left_is_higher && right_is_higher && up_is_higher && down_is_higher) {
                sum_of_risks += 1 + lines[y][x] - '0';
            }

        }
    }
    int part_1_solution = sum_of_risks;

    int part_2_solution = -1;

    // Display final results
    std::cout << "Day 9:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
