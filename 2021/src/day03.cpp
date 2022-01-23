#include <fstream>
#include <vector>
#include <iostream>
#include <string>

char most_common_bit_at_position(const std::vector<std::string>& values, int position)
{
    int bitcount = 0;

    for (auto code : values) {
        char bit_c = code[position];
        if (bit_c == '1') {
            bitcount++;
        }
        else {
            bitcount--;
        }
    }

    if (bitcount >= 0) return '1';
    return '0';
}

char least_common_bit_at_position(const std::vector<std::string>& values, int position)
{
    int bitcount = 0;

    for (auto code : values) {
        char bit_c = code[position];
        if (bit_c == '1') {
            bitcount++;
        }
        else {
            bitcount--;
        }
    }

    if (bitcount >= 0) return '0';
    return '1';
}

int day03_1()
{
    std::ifstream infile("input/day03.txt");
    std::vector<std::string> codes;
    std::string str;
    while (getline(infile, str)) {
        codes.push_back(str);
    }

    unsigned int gamma = 0;
    for (int i=0; i<12; i++)  {
        if('1' == most_common_bit_at_position(codes, i)) {
            gamma |= (1 << (11 - i));
        }
    }
    return gamma * ((~gamma) & 0xFFF);
}

unsigned int bitstring_to_uint(std::string bitstring)
{
    unsigned int result = 0;
    for (int i=bitstring.size()-1; i>=0; i--) {
        char bit_c = bitstring[i];
        if (bit_c == '1') {
            result += (1 << (bitstring.size()-1-i));
        }
    }
    return result;
}

unsigned int get_oxygen_generator_rating(std::vector<std::string> values, int numBits)
{
    int current_bit = 0;
    while(values.size() > 1) {
        char bit_to_filter = most_common_bit_at_position(values, current_bit);
        for (int i=values.size()-1; i>=0; i--) {
            if (
               ( (bit_to_filter == '0') && (values[i][current_bit] == '1') ) ||
               ( (bit_to_filter == '1')  && (values[i][current_bit] == '0') )
               )
            {
                values.erase(values.begin() + i);
            }
        }
        current_bit++;
    }

    unsigned int og = bitstring_to_uint(values[0]);
    return og;
}

unsigned int get_co2_scrubber_rating(std::vector<std::string> values, int numBits)
{
    int current_bit = 0;
    while(values.size() > 1) {
        char bit_to_filter = least_common_bit_at_position(values, current_bit);
        for (int i=values.size()-1; i>=0; i--) {
            if (
               ( (bit_to_filter == '0') && (values[i][current_bit] == '1') ) ||
               ( (bit_to_filter == '1')  && (values[i][current_bit] == '0') )
               )
            {
                values.erase(values.begin() + i);
            }
        }
        current_bit++;
    }

    unsigned int co = bitstring_to_uint(values[0]);
    return co;
}

int day03_2()
{
    std::ifstream infile("input/day03.txt");
    std::vector<std::string> codes;
    std::string str;
    while (getline(infile, str)) {
        codes.push_back(str);
    }

    unsigned int oxygen_generator_rating = get_oxygen_generator_rating(codes, 12);
    unsigned int CO2_scrubber_rating = get_co2_scrubber_rating(codes, 12);
    unsigned int life_support_rating =
        oxygen_generator_rating * CO2_scrubber_rating;
    return life_support_rating;
}
