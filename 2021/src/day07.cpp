#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <limits>

int total_cost(std::vector<int> crab_positions, int position)
{
    int sum = 0;
    for (auto cp: crab_positions) {
        sum += abs(cp - position);
    }
    return sum;
}

int variable_cost(int d) {
    return (d * (d+1)) / 2;
}

int updated_total_cost(std::vector<int> crab_positions, int position)
{
    int sum = 0;
    for (auto cp: crab_positions) {
        sum += variable_cost(abs(cp - position));
    }
    return sum;
}

void day07(std::string& input_path)
{
    std::ifstream infile(input_path);

    std::vector<int> crab_positions;
    int crab;
    char comma;
    while(infile >> crab) {
        crab_positions.push_back(crab);
        infile >> comma;
    }

    int min_pos = *std::min_element(crab_positions.begin(), crab_positions.end());
    int max_pos = *std::max_element(crab_positions.begin(), crab_positions.end());

    // part 1
    int min_fuel = std::numeric_limits<int>::max();
    for (int i=min_pos; i<max_pos; i++) {
        int current_cost = total_cost(crab_positions, i);
        if (current_cost < min_fuel) {
            min_fuel = current_cost;
        }
    }
    int part_1_solution = min_fuel;

    // part 2
    min_fuel = std::numeric_limits<int>::max();
    for (int i=min_pos; i<max_pos; i++) {
        int current_cost = updated_total_cost(crab_positions, i);
        if (current_cost < min_fuel) {
            min_fuel = current_cost;
        }
    }
    int part_2_solution = min_fuel;

    // Display final results
    std::cout << "Day 7:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
