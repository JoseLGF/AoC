#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <iostream>

std::vector<std::string> get_input(int day, bool test = false)
{
    std::string filename =
        std::string((test ? "test_" : "input_")) +
        ((day < 10) ? "0" : "") +
        (std::to_string(day)) +
        ".txt";

    std::ifstream file(filename);
    std::vector<std::string> out;
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            out.push_back(line);
        }

        file.close();
    }
    else {
        std::cout << "Failed to open file " + filename << std::endl;
        throw std::logic_error("Failed to open file " + filename);
    }

    return out;
}

std::vector<std::string> split_line(const std::string& str, const char delimiter = ',')
{
    std::stringstream ss(str);
    std::string token;
    std::vector<std::string> result;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}