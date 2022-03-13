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

int calculate_syntax_error_score(std::string line)
{
    auto char_cost = [] (char delim) {
        if (delim == ')') return 3;
        if (delim == ']') return 57;
        if (delim == '}') return 1197;
        if (delim == '>') return 25137;
        return 0;
    };

    std::stack<char> chars;

    for (auto c: line) {
        // Opening parens are always accepted
        if (c == '(' ||
            c == '[' ||
            c == '{' ||
            c == '<')
        {
            chars.push(c);
        }
        else {
            // A closing paren on an empty stack is error
            if (chars.empty()) {
                return char_cost(c);
            }
            // closing parens must match top of stack
            if (
                 ((c == ')') && (chars.top() == '(')) ||
                 ((c == ']') && (chars.top() == '[')) ||
                 ((c == '}') && (chars.top() == '{')) ||
                 ((c == '>') && (chars.top() == '<'))
               )
            {
                chars.pop();
            }
            else {
                return char_cost(c);
            }
        }
    }

    return 0;
}

void day10()
{
    int part_1_solution = -1;
    int part_2_solution = -1;
    std::ifstream infile("input/day10.txt");

    // Parse data
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    // Part 1
    int syntax_error_score = 0;
    for (auto l: lines) {
        syntax_error_score += calculate_syntax_error_score(l);
    }
    part_1_solution = syntax_error_score;


    // Display final results
    std::cout << "Day 10:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
