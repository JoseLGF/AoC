#include <string>
#include <vector>
#include <fstream>

std::string
get_input_string(const std::string& input_path);

std::vector<std::string>
get_input(const std::string& input_path);

std::vector<std::string>
tokenize_string(std::string);

std::vector<int>
read_comma_separated_ints_line(const std::string& line);
