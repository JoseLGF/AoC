#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <limits>

struct LogLine
{
    std::vector<std::string> signal_patterns;
    std::vector<std::string> output_values;

    LogLine(std::vector<std::string> patterns, std::vector<std::string> values) {
        signal_patterns = patterns;
        output_values = values;
    }
};

std::vector<std::string> generate_nums (std::string guess)
{
    std::vector<std::string> nums(10);
    nums[0] = std::string() + guess[0] + guess[1] + guess[2] + guess[4] + guess[5] + guess[6];
    nums[1] = std::string() +                       guess[2]                       + guess[5]           ;
    nums[2] = std::string() + guess[0]            + guess[2] + guess[3] + guess[4]            + guess[6];
    nums[3] = std::string() + guess[0]            + guess[2] + guess[3]            + guess[5] + guess[6];
    nums[4] = std::string() +            guess[1] + guess[2] + guess[3]            + guess[5]           ;
    nums[5] = std::string() + guess[0] + guess[1]            + guess[3]            + guess[5] + guess[6];
    nums[6] = std::string() + guess[0] + guess[1]            + guess[3] + guess[4] + guess[5] + guess[6];
    nums[7] = std::string() + guess[0]            + guess[2]                       + guess[5]           ;
    nums[8] = std::string() + guess[0] + guess[1] + guess[2] + guess[3] + guess[4] + guess[5] + guess[6];
    nums[9] = std::string() + guess[0] + guess[1] + guess[2] + guess[3]            + guess[5] + guess[6];

    for (auto& num: nums) {
        std::sort(num.begin(), num.end());
    }

    return nums;
}

bool is_guess_correct(std::string guess, LogLine& line)
{
    // Assume that line is already sorted
    auto nums = generate_nums (guess);

    // Sort guess
    for (auto& g: nums) {
        std::sort(g.begin(), g.end());
    }
    std::sort(nums.begin(), nums.end());

    // Check that all generated strings exist in the ten numbers of the entry
    bool strings_match = true;
    for (auto signal: line.signal_patterns) {
        auto found = std::find(nums.begin(), nums.end(), signal);
        if (found == nums.end()) {
            return false;
        }
    }
    return true;
}

int find_output_value(LogLine line)
{
    // Sort the ten unique signals
    for (auto& signal: line.signal_patterns) {
        std::sort(signal.begin(), signal.end());
    }
    std::sort(line.signal_patterns.begin(), line.signal_patterns.end());

    // Sort each output value individually
    for (auto& output: line.output_values) {
        std::sort(output.begin(), output.end());
    }

    // Generate a guess
    std::string guess = "deafgbc";
    std::vector<int> outputs;
    while (! is_guess_correct(guess, line)) {
        std::next_permutation(guess.begin(), guess.end());
    }

    auto nums = generate_nums(guess);
    for (auto output: line.output_values) {
        auto it = nums.begin();
        auto found = std::find(nums.begin(), nums.end(), output);
        outputs.push_back(found - it);
    }

    // Convert outputs into number
    int output = 0;
    for (auto o: outputs) {
        output = 10 * output + o;
    }

    // Get the values on the output side
    return output;
}

void day08()
{
    std::ifstream infile("input/day08.txt");

    // Parse data
    std::string line;
    std::string token;
    std::vector<LogLine> loglines;
    while (std::getline(infile, line)) {
        std::vector<std::string> patterns;
        std::vector<std::string> values;
        std::istringstream iss(line);

        // Ten unique digit sequences
        for (int i=0; i<10; i++) {
            iss >> token;
            patterns.push_back(token);
        }

        // delimiter
        iss >> token;

        // four output digits
        for (int i=0; i<4; i++) {
            iss >> token;
            values.push_back(token);
        }

        loglines.push_back(LogLine(patterns, values));
    }

    // Count number of digits with 1,4,7, or 8 in the output values
    int count_digits1478 = 0;
    for (auto line: loglines) {
        for (auto val: line.output_values) {
            if ( (val.size() == 2) ||
                 (val.size() == 4) ||
                 (val.size() == 7) ||
                 (val.size() == 3) )
            {
                count_digits1478 ++;
            }
        }
    }

    int part_1_solution = count_digits1478;

    // Part 2 - Find all correct segment values and add the values at outputs
    int output_sum = 0;
    for (auto line: loglines) {
        output_sum += find_output_value(line);
    }

    int part_2_solution = output_sum;

    // Display final results
    std::cout << "Day 8:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
