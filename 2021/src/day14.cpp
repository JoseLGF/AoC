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


class PolymerFormula
{
    // Original string template
    std::string _template;

    int num_steps;
    char rule_matrix[255][255];
    uint64_t pair_counts[255][255];
    std::vector<uint64_t> char_counts;

    public:
    PolymerFormula(std::vector<std::string> lines) {
        for (int i=0;i<255;i++) {
        for (int j=0;j<255;j++) {
            rule_matrix[i][j] = 0;
            pair_counts[i][j] = 0;
        }}
        char_counts = std::vector<uint64_t>(255,0);
        num_steps = 0;
        int stage = 0;

        for (auto line: lines) {
            if (line.empty()) {
                stage = 1;
                continue;
            }

            if (0 == stage) {
                _template = line;
                for(auto c: _template) {
                    char_counts[c] ++;
                }
            }
            if (1 == stage) {
                // For matrix representation
                char first_index = line[0];
                char second_index = line[1];
                char sub_char = line[6];
                rule_matrix[first_index][second_index]
                    = sub_char;
            }
        }
            // Populate pair counts
            for(int i=0;i<_template.size()-1;i++) {
                char index_1 = _template[i];
                char index_2 = _template[i+1];
                pair_counts[index_1][index_2]++;
            }
    }

    void run_steps(int n) {
        while (num_steps < n) {
            step();
        }
    }

    void step_naive() {
        std::string new_template{};
        new_template.reserve(_template.size()*2);

        new_template += _template[0];
        // Capture all pairs
        for(int i=0; i<_template.size()-1;i++) {
            char insertion =
                rule_matrix[_template[i]][_template[i+1]];
            if (insertion >= 0) {
                new_template += insertion;
            }
            new_template += _template[i+1];
        }
        _template = new_template;
        num_steps++;
    }

    void step() {
        struct Operation {
            char i;
            char j;
            char insertion;
            uint64_t count;
        };
        std::vector<Operation> operations;
        for (auto i='A';i<='Z';i++) {
        for (auto j='A';j<='Z';j++) {
            uint64_t p_count = pair_counts[i][j];
            if (p_count >0) {
                // Check if there is a rule for this pair
                char insertion = rule_matrix[i][j];
                if (insertion > 0) {
                    operations.push_back(Operation(i,j,insertion,p_count));
                }
            }
        }
        }
        // Apply all operations
        for (auto& op: operations) {
            char i = op.i;
            char j = op.j;
            char insertion = op.insertion;
            uint64_t p_count = op.count;
            pair_counts[i][insertion] += p_count;
            pair_counts[insertion][j] += p_count;
            char_counts[insertion] += p_count;
            pair_counts[i][j] -= p_count;
        }
        num_steps++;
    }

    void print() {
        std::cout << _template << std::endl;
    }

    void print_rule_matrix() {
        std::cout << "Rule matrix:" << std::endl;
        std::cout << "  ABCDEFGHIJKLMNOPQRSTUVWXYZ" << std::endl;
        for (int i='A';i<='Z';i++) {
            std::cout << (char)i << ":";
            for (int j='A';j<='Z';j++) {
                char insertion = rule_matrix[i][j];
                if (insertion >= 0) {
                    std::cout << (char)insertion;
                }
                else {
                    std::cout << '.';
                }
            }
            std::cout << std::endl;
        }
    }

    void print_pair_counts() {
        std::cout << "Pair counts:" << std::endl;
        for (char i='A';i<='Z';i++) {
        for (char j='A';j<='Z';j++) {
            uint64_t count = pair_counts[i][j];
            if (count > 0) {
                std::cout << (char)i
                          << (char)j
                          << ":" << count << std::endl;
            }
        }
        }
    }

    uint64_t most_minus_least_common_chars () {
        auto new_char_counts = char_counts;
        // Remove zeroes from the counts
        auto isZero = [] (int i) {
            return i == 0;
        };
        std::vector<uint64_t>::iterator newIter =
            std::remove_if(
                new_char_counts.begin(),
                new_char_counts.end(),
                isZero);
        new_char_counts.resize(
                newIter - new_char_counts.begin());

        uint64_t max =
            *std::max_element(new_char_counts.begin(),
                new_char_counts.end());
        uint64_t min =
            *std::min_element(new_char_counts.begin(),
                new_char_counts.end());
        return max - min;
    }
};

void day14(std::string& input_path)
{
    int part_1_solution = -1;
    uint64_t part_2_solution = -1;
    std::ifstream infile(input_path);

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
    formula.run_steps(40);
    //formula.print();
    part_2_solution = formula.most_minus_least_common_chars();

    // Display final results
    std::cout << "Day 14:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
