#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <limits>
#include <unordered_set>
#include <utility>
#include <stack>

class OctopusField
{
	int height;
	int width;
    std::vector<int> energy_levels;
    // Indicates that an octopus has already flashed in the current iteration
    std::vector<unsigned char> flashed;
    // Indicates that the data structure has already been initialized
    bool initialized = false;
    int total_flashes;
    int steps;

public:

    OctopusField(std::vector<std::string> lines)
    {
        height = lines.size();
        width  = lines[0].size();
        total_flashes = 0;
        steps = 0;

        for (auto& line: lines) {
            for (auto c : line) {
                energy_levels.push_back(c - '0');
                flashed.push_back(false);
            }
        }

        initialized = true;
    }

    void display()
    {
        if (!initialized) {
            std::cout << "Octopus field not initialized" << std::endl;
            return;
        }

        for (int y=0; y<height; y++) {
            for (int x=0; x<width; x++) {
                std::cout << char(energy_levels[x+width*y] + '0');
            }
            std::cout << std::endl;
        }
    }

    void simulate_step()
    {
        // Step 1: Increase energy levels of every octopus by one.
        for (int& e: energy_levels) {
            e++;
        }

        // Step 2: Any octopus with an energy level greater than 9 flashes
        bool repeat = true;
        while (repeat) {
            repeat = false;
            for (int y=0; y<height; y++) {
                for (int x=0; x<width; x++) {
                    int current_index = get_index(x, y);
                    int energy_level = energy_levels[current_index];
                    if ( (energy_level > 9) && (!flashed[current_index]) ) {
                        flashed[current_index] = true;
                        propagate(x, y);
                        repeat = true;
                    }
                }
            }
        }
        // Step 3: All octopus that flashed in the step are reset to 0
        for (auto& e: energy_levels) {
            if (e>9) e = 0;
        }
        for (auto& f: flashed) {
            if (f) {
                f = false;
                total_flashes++;
            }
        }

        steps++;
    }

    // Increase energy levels of neighboring octopuses, without flashing
    // Neighbors include diagonally adjacent
    void propagate(int x, int y) {
        for (int xx = x-1; xx<=x+1; xx++) {
            for (int yy = y-1; yy<=y+1; yy++) {
                if (
                    (xx >=0) && (xx < width)  &&
                    (yy >=0) && (yy < height)
                    ) {
                    int index = get_index(xx, yy);
                        energy_levels[index]++;
                }
            }
        }
    }

    int get_index(int x, int y) {
        return y * width + x;
    }

    int get_total_flashes() {
        return total_flashes;
    }

    void simulate_until_step(int limit) {
        while(steps<limit) {
            simulate_step();
        }
    }

};

void day11()
{
    int part_1_solution = -1;
    int part_2_solution = -1;
    std::ifstream infile("../input/day11.txt");

    // Parse data
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    // Init
    OctopusField of(lines);
    of.display();

    // Part 1
    of.simulate_until_step(100);
    part_1_solution = of.get_total_flashes();

    // Part 2

    // Display final results
    std::cout << "Day 11:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
