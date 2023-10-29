#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

#include "common.h"

int priority(char c) {

    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 1;
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 27;
    }
    return 0;
}

int part1(std::vector<std::string>& lines)
{
    int sumOfPriorities = 0;

    for (auto rucksack: lines) {
        int length = rucksack.size();
        auto compartment1 = rucksack.substr(0, length/2);
        auto compartment2 = rucksack.substr(length/2);

        // Create bins for character counts of compartment 1
        int char_counts[255] {};

        // Count occurences of chars in compartment 1
        for (auto c: compartment1) {
            char_counts[c] += 1;
        }

        // Check occurences of chars from comp 2 in comp 1
        for (auto c: compartment2) {
            if (char_counts[c] > 0) {
            int prio = priority(c);
            sumOfPriorities += prio;
            break;
            }
        }
    }
    return sumOfPriorities;
}

std::vector<std::vector<std::string>>
make_groups (std::vector<std::string>& lines)
{
    std::vector<std::vector<std::string>> out;
    for (int i=0; i<lines.size(); i+=3) {
        std::vector<std::string> group;
        group.push_back(lines[i]);
        group.push_back(lines[i+1]);
        group.push_back(lines[i+2]);
        out.push_back(group);
    }
    return out;
}

int part2(std::vector<std::string>& lines)
{
    auto groups = make_groups(lines);
    std::vector<char> badges;

    for (auto group: groups) {
        badges.push_back(find_badge(group));
    }
    
    return 0;
} 

void day03(std::string& input_path) {
    std::cout << "Day 3:" << std::endl;

    std::vector<std::string> lines =
    get_input(input_path);

    std::cout << part1(lines) << std::endl;
}
