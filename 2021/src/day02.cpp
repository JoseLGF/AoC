#include <fstream>
#include <vector>
#include <iostream>

int day02_1(std::string& input_path) {
    std::ifstream infile(input_path);
    std::string command;
    int parameter;

    int depth = 0;
    int distance = 0;
    while(infile >> command && infile >> parameter)
    {
        switch (command[0]) {
            case 'u':
                depth -= parameter;
                break;
            case 'd':
                depth += parameter;
                break;
            case 'f':
                distance += parameter;
                break;
            default:
                break;
        }
    }

    return depth * distance;
}

int day02_2(std::string& input_path) {
    std::ifstream infile(input_path);
    std::string command;
    int parameter;

    int aim = 0;
    int depth = 0;
    int distance = 0;
    while(infile >> command && infile >> parameter)
    {
        switch (command[0]) {
            case 'u':
                aim -= parameter;
                break;
            case 'd':
                aim += parameter;
                break;
            case 'f':
                distance += parameter;
                depth += (aim * parameter);
                break;
            default:
                break;
        }
    }

    return depth * distance;
}

void day02(std::string& input_path)
{
    std::cout << "Day 2:" << std::endl;
    std::cout << day02_1(input_path) << std::endl;
    std::cout << day02_2(input_path) << std::endl;
}
