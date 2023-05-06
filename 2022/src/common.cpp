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
