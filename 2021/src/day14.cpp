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
#include <set>

struct Rule
{
    std::string insertion_pair;
    char insertion_element;

    Rule(std::string line) {
        insertion_pair = line.substr(0,2);
        insertion_element = line[6];
    }
};

class PolymerFormula
{
    std::string _template;
    std::vector<Rule> rules;
    int num_steps;

    // Derivate representation
    char rule_matrix[26][26] {-1};

    public:
    PolymerFormula(std::vector<std::string> lines) {
        num_steps = 0;
        int stage = 0;
        for (auto line: lines) {
            if (line.empty()) {
                stage = 1;
                continue;
            }

            if (0 == stage) {
                _template = line;
            }
            if (1 == stage) {
                rules.push_back(Rule(line));
                // For matrix representation
                int first_index = line[0];
                int second_index = line[1];
                char sub_char = line[6];
                rule_matrix[first_index][second_index]
                    = sub_char;
            }
        }
    }

    void run_steps(int n) {
        while (num_steps < n) {
            step();
            std::cout << "Step " << num_steps << " complete" << std::endl;
        }
    }

    void step() {
        std::vector<std::string> pairs;
        std::vector<char> insertions;
        // Capture all pairs
        for(int i=0; i<_template.size()-1;i++) {
            pairs.push_back(_template.substr(i,2));
        }
        // Capture the insertions
        for(auto p: pairs) {
            char insertion = rule_matrix[p[0]][p[1]];
            insertions.push_back(insertion);
        }
        // Build new template with found insertions
        std::string new_template{};
        // Add first letter of first pair
        new_template += pairs[0][0];
        for(int i=0; i<pairs.size(); i++) {
            auto p = pairs[i];
            auto insertion = insertions[i];
            if (insertion >= 0) {
                new_template += insertion;
            }
            new_template += p[1];
        }
        _template = new_template;
        num_steps++;
    }

    void print() {
        std::cout << _template << std::endl;
    }

    int most_minus_least_common_chars () {
        std::vector<int> char_counts(255, 0);

        for (auto c: _template) {
            char_counts[c]++;
        }

        // Remove zeroes from the counts
        // Let op! This will violate the match between
        // index and the corresponding char
        auto isZero = [] (int i)
        {
            return i == 0;
        };

        std::vector<int>::iterator newIter =
            std::remove_if(
                char_counts.begin(),
                char_counts.end(),
                isZero);
        char_counts.resize(newIter -  char_counts.begin() );


        int max = *std::max_element(char_counts.begin(),
                char_counts.end());
        int min = *std::min_element(char_counts.begin(),
                char_counts.end());


        return max - min;
    }

};

void day14()
{
    int part_1_solution = -1;
    int part_2_solution = -1;
    std::ifstream infile("input/day14.txt");

    // Parse data
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    // Init
    PolymerFormula formula(lines);

    // Part 1
    formula.run_steps(10);
    //formula.print();
    part_1_solution = formula.most_minus_least_common_chars();


    // Part 2
    //formula.run_steps(40);
    //std::cout << "Calculation of 40 steps complete" << std::endl;
    //formula.print();
    //part_2_solution = formula.most_minus_least_common_chars();

    // Display final results
    std::cout << "Day 14:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
