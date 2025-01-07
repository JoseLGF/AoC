#include "common.h"
#include <sstream>

using namespace std;

std::string
get_input_string(const std::string& input_path)
{
    std::ifstream t(input_path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string out = buffer.str();
    return out;
}

std::vector<std::string>
get_input(const std::string& input_path)
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

    while (std::getline(ss, intermediate, ' ')) {
        tokens.push_back(intermediate);
    }

    return tokens;
}

std::vector<int>
read_comma_separated_ints_line(const std::string& line)
{
    stringstream ss;
    ss << line;

    vector<int> out;
    string temp;
    while (getline(ss, temp, ',')) {
        out.push_back(stoi(temp));
    }
    return out;
}