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

std::string get_completing_characters(std::string line)
{
    // Returns the characters necessary to close the current
    // line. If the line is complete, or if it is corrupted,
    // return an empty string
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
                return "";
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
                return "";
            }
        }
    }

    std::string out;
    while(! chars.empty()) {
        switch (chars.top()) {
            case '(' : out += ')'; break;
            case '[' : out += ']'; break;
            case '{' : out += '}'; break;
            case '<' : out += '>'; break;
        }
        chars.pop();
    }

    return out;
}

unsigned long get_autocomplete_score(std::string completing_chars)
{
    unsigned long score = 0;

    for (auto c: completing_chars) {
        score *= 5;
        switch(c) {
            case ')': score += 1; break;
            case ']': score += 2; break;
            case '}': score += 3; break;
            case '>': score += 4; break;
        }
    }

    return score;
}

void day10(std::string& input_path)
{
    int part_1_solution = -1;
    unsigned long part_2_solution = -1;
    std::ifstream infile(input_path);

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

    // Part 2
    std::vector<unsigned long> autocomplete_scores;
    for (auto l: lines) {
        unsigned long current_score =
            get_autocomplete_score(
                    get_completing_characters(l));
        if (0 != current_score) {
            autocomplete_scores.push_back(current_score);
        }
    }
    std::sort(autocomplete_scores.begin(),
              autocomplete_scores.end());
    part_2_solution = autocomplete_scores[
        autocomplete_scores.size()/2];


    // Display final results
    std::cout << "Day 10:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
