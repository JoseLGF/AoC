#include <fstream>
#include <vector>
#include <iostream>
#include <forward_list>

int day03_1()
{
    std::ifstream infile("input/day03.txt");
    std::string diagnostic;
    std::vector<int> bitCounts(12, 0);

    while (infile >> diagnostic) {
        bitCounts[0] +=  ((diagnostic[0] == '1') ? 1 : -1);
        bitCounts[1] +=  ((diagnostic[1] == '1') ? 1 : -1);
        bitCounts[2] +=  ((diagnostic[2] == '1') ? 1 : -1);
        bitCounts[3] +=  ((diagnostic[3] == '1') ? 1 : -1);
        bitCounts[4] +=  ((diagnostic[4] == '1') ? 1 : -1);
        bitCounts[5] +=  ((diagnostic[5] == '1') ? 1 : -1);
        bitCounts[6] +=  ((diagnostic[6] == '1') ? 1 : -1);
        bitCounts[7] +=  ((diagnostic[7] == '1') ? 1 : -1);
        bitCounts[8] +=  ((diagnostic[8] == '1') ? 1 : -1);
        bitCounts[9] +=  ((diagnostic[9] == '1') ? 1 : -1);
        bitCounts[10] += ((diagnostic[10] == '1') ? 1 : -1);
        bitCounts[11] += ((diagnostic[11] == '1') ? 1 : -1);
    }

    unsigned int gamma = 0;
    if (bitCounts[0] > 0)  gamma |= 0x800;
    if (bitCounts[1] > 0)  gamma |= 0x400;
    if (bitCounts[2] > 0)  gamma |= 0x200;
    if (bitCounts[3] > 0)  gamma |= 0x100;
    if (bitCounts[4] > 0)  gamma |= 0x080;
    if (bitCounts[5] > 0)  gamma |= 0x040;
    if (bitCounts[6] > 0)  gamma |= 0x020;
    if (bitCounts[7] > 0)  gamma |= 0x010;
    if (bitCounts[8] > 0)  gamma |= 0x008;
    if (bitCounts[9] > 0)  gamma |= 0x004;
    if (bitCounts[10] > 0) gamma |= 0x002;
    if (bitCounts[11] > 0) gamma |= 0x001;

    return gamma * ((~gamma) & 0xFFF);
}

int day03_2()
{
    std::ifstream infile("input/day03.txt");
    std::string diagnostic;
    std::vector<int> bitCounts(12, 0);
    std::forward_list<std::string> oxygen_numbers;
    std::forward_list<std::string> co2_numbers;

    while (infile >> diagnostic) {
        oxygen_numbers.push_front(diagnostic);
        co2_numbers.push_front(diagnostic);
        bitCounts[0] +=  ((diagnostic[0] == '1') ? 1 : -1);
        bitCounts[1] +=  ((diagnostic[1] == '1') ? 1 : -1);
        bitCounts[2] +=  ((diagnostic[2] == '1') ? 1 : -1);
        bitCounts[3] +=  ((diagnostic[3] == '1') ? 1 : -1);
        bitCounts[4] +=  ((diagnostic[4] == '1') ? 1 : -1);
        bitCounts[5] +=  ((diagnostic[5] == '1') ? 1 : -1);
        bitCounts[6] +=  ((diagnostic[6] == '1') ? 1 : -1);
        bitCounts[7] +=  ((diagnostic[7] == '1') ? 1 : -1);
        bitCounts[8] +=  ((diagnostic[8] == '1') ? 1 : -1);
        bitCounts[9] +=  ((diagnostic[9] == '1') ? 1 : -1);
        bitCounts[10] += ((diagnostic[10] == '1') ? 1 : -1);
        bitCounts[11] += ((diagnostic[11] == '1') ? 1 : -1);
    }

    int current_bit = 0;
    // Find the oxygen generator rating
    while (std::distance(oxygen_numbers.begin(),
                         oxygen_numbers.end()) != 1)
    {
        bool most_common_bit = bitCounts[0] >= 0 ? true : false;

    }


    int oxygen_generator_rating;
    int CO2_scrubber_rating;
    int life_support_rating =
        oxygen_generator_rating * CO2_scrubber_rating;
    return -1;
}
