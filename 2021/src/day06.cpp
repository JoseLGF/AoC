#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdint>

class Fish_simulator
{
    int num_buckets = 9;
    std::vector<uint64_t> fish_buckets;

public:

    Fish_simulator(std::vector<unsigned int> initial_state) {
        fish_buckets = std::vector<uint64_t>(num_buckets,0);
        // Load buckets
        for (auto f: initial_state) {
            fish_buckets[f] ++;
        }
    }

    void simulate() {
        uint64_t new_fish = 0;
        for (int i=0; i<num_buckets; i++) {
            if (0 == i) {
                new_fish = fish_buckets[0];
            }
            else {
                fish_buckets[i-1] = fish_buckets[i];
            }
        }
        // Update new fish
        fish_buckets[8] = new_fish;
        fish_buckets[6] += new_fish;
    }

    void print_buckets() {
        std::cout << "Buckets: ";
        for (auto b : fish_buckets) {
            std::cout << b << " ";
        }
        std::cout << std::endl;
    }

    uint64_t get_num_fish() {
        return std::accumulate(fish_buckets.begin(),
                                                fish_buckets.end(),
                                                (uint64_t)0);
    }

};

std::vector<unsigned int> simulate_fish(std::vector<unsigned int> state)
{
    std::vector<unsigned int> out;
    for(auto f: state) {
        if (f >= 1) {
            out.push_back(f-1);
        }
        else {
            out.push_back(6);
            out.push_back(8);
        }
    }

    return out;
}

void day06()
{
    std::ifstream infile("input/day06.txt");

    int num_days = 80;

    std::vector<unsigned int> initial_state;
    unsigned int f;
    char c;
    while (infile >> f)
    {
        initial_state.push_back(f);
        infile >> c;
    }

    /*
    std::cout << "Initial state: ";
    for (auto t: initial_state)
        std::cout << t << " ";
    std::cout << std::endl;
    */

    std::vector<unsigned int> fish = initial_state;

    for (int i=0; i<num_days; i++) {
        fish = simulate_fish(fish);
        /*
        std::cout << "After " << i+1 << " days: ";
        for (auto t: fish)
            std::cout << t << " ";
        std::cout << std::endl;
        */
    }
    unsigned int part_1_solution = fish.size();

    // Part 2
    num_days = 256;
    fish = initial_state;

    Fish_simulator simulator(fish);

    for (int i=0; i<num_days; i++) {
        simulator.simulate();
        //std::cout << "After " << i+1 << " days: ";
        //simulator.print_buckets();
    }
    //std::cout << "After " << num_days << " days: ";
    //std::cout << simulator.get_num_fish() << std::endl;
    uint64_t part_2_solution = simulator.get_num_fish();

    // Display final results
    std::cout << "Day 6:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
