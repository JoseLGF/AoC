#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

std::vector<int> simulate_fish(std::vector<int> state)
{
    std::vector<int> out;
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

    std::vector<int> initial_state;
    int f;
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

    std::vector<int> fish = initial_state;

    for (int i=0; i<num_days; i++) {
        fish = simulate_fish(fish);
        /*
        std::cout << "After " << i+1 << " days: ";
        for (auto t: fish)
            std::cout << t << " ";
        std::cout << std::endl;
        */
    }



    // Display final results
    std::cout << "Day 6:" << std::endl;
    std::cout << fish.size() << std::endl;
    std::cout << -1 << std::endl;
}
