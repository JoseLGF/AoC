#include <bits/stdc++.h>

#include "common.h"

std::vector<std::string>
get_input(std::string& input_path)
{
    std::ifstream infile(input_path);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(infile, line))
    {
        lines.push_back(line);
    }
    
    return lines;
}

std::vector<std::string>
tokenize_string(std::string line)
{
    using namespace std;
    std::vector<std::string> tokens;

    stringstream ss(line);
    string intermediate;

    while(getline(ss, intermediate, ' ')) {
        tokens.push_back(intermediate);
    }

    return tokens;
}