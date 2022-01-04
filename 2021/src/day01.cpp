#include <fstream>
#include <vector>
#include <iostream>

int day01_1() {
    std::ifstream infile("input/day01.txt");
    std::vector<int> measurements;
    int measurement;
    while(infile >> measurement) measurements.push_back(measurement);

    int increasing_measurements = 0;
    for (int i=1; i<measurements.size(); i++) {
        if (measurements[i] > measurements[i-1])
            increasing_measurements++;
    }

    return increasing_measurements;
}

int day01_2() {
    std::ifstream infile("input/day01.txt");
    std::vector<int> measurements;
    int measurement;
    while(infile >> measurement) measurements.push_back(measurement);

    int previous_window =  measurements[0]
                        + measurements[1]
                        + measurements[2];
    int increasing_windows = 0;
    for (int i=0; i<measurements.size()-2; i++) {
        int current_window =
            previous_window - measurements[i] + measurements[i+3];
        if (current_window > previous_window) increasing_windows++;
    }

    return increasing_windows;

}
