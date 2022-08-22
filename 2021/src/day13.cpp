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

struct Dot
{
    int x;
    int y;

    Dot(std::string line) {
        std::stringstream sl(line);
        char sep;
        sl >> x;
        sl >> sep;
        sl >> y;
    }

    Dot(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

enum FoldAxis
{
    XAxis = 0,
    YAxis = 1
};

struct Fold
{
    FoldAxis axis;
    int coordinate;

    Fold(std::string line) {
        std::string axis_string;
        std::string coordinate_string;

        std::vector<std::string> tokens;
        std::stringstream sl(line);
        getline(sl, axis_string, '=');
        getline(sl, coordinate_string);

        if (axis_string.back() == 'x') {
            axis = FoldAxis::XAxis;
        }
        else {
            axis = FoldAxis::YAxis;
        }

        coordinate = stoi(coordinate_string);
    }
};

class Problem
{
    // Source of truth
    std::vector<Dot> dots;
    std::vector<Fold> folds;

    // Other representations must be updated according to SOT
    std::vector<int> dots_x;
    std::vector<int> dots_y;

    std::vector<std::vector<bool>> grid;

    public:
    Problem(std::vector<std::string> lines) {
        //std::cout << "Initializing problem" << std::endl;
        int stage = 0;
        for (auto line: lines) {
            if (line.empty()) {
                stage = 1;
                continue;
            }

            if (0 == stage) {
                dots.push_back(Dot(line));
            }
            if (1 == stage) {
                folds.push_back(Fold(line));
            }
        }

        update_representations();

    }

    void next_fold() {
        Fold next = folds.front();
        folds.erase(folds.begin());

        if (next.axis == FoldAxis::XAxis) {
            fold_vertical(next.coordinate);
        }
        if (next.axis == FoldAxis::YAxis) {
            fold_horizontal(next.coordinate);
        }
    }

    void fold_all() {
        while (!folds.empty()) {
            next_fold();
        }
    }

    void display_grid() {
        for (int y=0; y<grid[0].size(); y++) {
            for (int x=0; x<grid.size(); x++) {
                bool v = grid[x][y];
                if (v) {
                    std::cout << '#';
                }
                else {
                    std::cout << '.';
                }
            }
            std::cout << std::endl;
        }
    }

    int get_num_visible_dots() {
        return dots.size();
    }

    private:

    void update_representations() {
        dots_x.clear();
        dots_y.clear();
        for (auto& dot: dots) {
            dots_x.push_back(dot.x);
            dots_y.push_back(dot.y);
        }

        update_grid();
    }

    void fold_vertical(int coordinate) {
        dots.clear();
        // the line is vertical
        for (int y=0; y<grid[0].size();y++) {
            for (int x=0;x<coordinate;x++) {
                int offset = coordinate - x;
                int twin = coordinate + offset;
                if (grid[twin][y] || grid[x][y]) {
                    grid[x][y] = true;
                    dots.push_back(Dot(x,y));
                }
            }
        }
        update_representations();
    }

    void fold_horizontal(int coordinate) {
        dots.clear();
        // the line is horizontal
        for (int x=0; x<grid.size();x++) {
            for (int y=0;y<coordinate;y++) {
                int offset = coordinate - y;
                int twin = coordinate + offset;
                if (grid[x][twin] || grid[x][y]) {
                    grid[x][y] = true;
                    dots.push_back(Dot(x,y));
                }
            }
        }
        update_representations();
    }

    void update_grid() {
        int x_max = *std::max_element(dots_x.begin(), dots_x.end());
        int y_max = *std::max_element(dots_y.begin(), dots_y.end());

        grid.clear();
        for (int i=0;i<x_max+1;i++) {
            grid.push_back(std::vector<bool>(y_max+1,false));
        }

        for (auto& dot: dots) {
            grid[dot.x][dot.y] = true;
        }
    }


};

void day13()
{
    int part_1_solution = -1;
    int part_2_solution = -1;
    std::ifstream infile("input/day13.txt");

    // Parse data
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    // Init
    Problem problem(lines);
    //problem.display_grid();

    // Part 1
    problem.next_fold();
    //problem.display_grid();
    part_1_solution = problem.get_num_visible_dots();


    // Part 2
    problem.fold_all();
    //problem.display_grid(); // draws LGHEGUEJ

    // Display final results
    std::cout << "Day 13:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << "LGHEGUEJ" << std::endl;
}
