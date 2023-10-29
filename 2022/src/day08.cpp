#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

#include "common.h"

using namespace std;

struct Tree
{
    int height;
    bool is_visible;
    int left_view;
    int right_view;
    int up_view;
    int down_view;
    int scenic_score;
};

void day08(std::string& input_path) {
    std::cout << "Day 8:" << std::endl;

    auto lines = get_input(input_path);

    vector<vector<Tree>> grid;

    int grid_height = lines.size();
    int grid_width  = lines[0].size();

    // Initialize grid
    for (auto& line: lines) {
        vector<Tree> row;
        for (auto& c: line) {
            row.push_back({c - '0', false, 0,0,0,0,0});
        }
        grid.push_back(row);
    }

    // Part 1

    // Calculate visibility from left
    for (int row=0; row<grid_height; row++) {
        int previous_height = -1;
        for (int col=0; col<grid_width; col++) {
            auto& tree = grid[row][col];
            if (tree.height > previous_height) {
                tree.is_visible = true;
                previous_height = tree.height;
            }
        }
    }
    // Calculate visibility from right
    for (int row=0; row<grid_height; row++) {
        int previous_height = -1;
        for (int col=grid_width-1; col>=0; col--) {
            auto& tree = grid[row][col];
            if (tree.height > previous_height) {
                tree.is_visible = true;
                previous_height = tree.height;
            }
        }
    }
    // Calculate visibility from top
    for (int col=0; col<grid_width; col++) {
        int previous_height = -1;
        for (int row=0; row<grid_height; row++) {
            auto& tree = grid[row][col];
            if (tree.height > previous_height) {
                tree.is_visible = true;
                previous_height = tree.height;
            }
        }
    }
    // Calculate visibility from bottom
    for (int col=0; col<grid_width; col++) {
        int previous_height = -1;
        for (int row=grid_height-1; row>=0; row--) {
            auto& tree = grid[row][col];
            if (tree.height > previous_height) {
                tree.is_visible = true;
                previous_height = tree.height;
            }
        }
    }

    // Part 2

    // Calculate scenic score for each individual tree
    for (int row=0; row<grid_height; row++) {
    for (int col=0; col<grid_width; col++) {
        auto& base_tree = grid[row][col];
        // Looking up
        for (int up_row=row-1; up_row>=0; up_row--) {
            auto up_tree = grid[up_row][col];
            if (base_tree.height > up_tree.height) {
                base_tree.up_view++;
            } else {
                base_tree.up_view++;
                break;
            }
        }
        // Looking down
        for (int down_row=row+1; down_row<grid_height; down_row++) {
            auto down_tree = grid[down_row][col];
            if (base_tree.height > down_tree.height) {
                base_tree.down_view++;
            } else {
                base_tree.down_view++;
                break;
            }
        }
        // Looking left
        for (int left_col=col-1; left_col>=0; left_col--) {
            auto left_tree = grid[row][left_col];
            if (base_tree.height > left_tree.height) {
                base_tree.left_view++;
            } else {
                base_tree.left_view++;
                break;
            }
        }
        // Looking right
        for (int right_col=col+1; right_col<grid_width; right_col++) {
            auto right_tree = grid[row][right_col];
            if (base_tree.height > right_tree.height) {
                base_tree.right_view++;
            } else {
                base_tree.right_view++;
                break;
            }
        }

        base_tree.scenic_score = base_tree.up_view * base_tree.down_view *
                                 base_tree.left_view * base_tree.right_view;
    }
    }

    // Display grid
    int max_scenic_score = 0;
    int visible_count = 0;
    for (auto row: grid) {
        for (auto tree : row) {
            if (tree.scenic_score > max_scenic_score) {
                max_scenic_score = tree.scenic_score;
            }
            if (tree.is_visible) {
                visible_count++;
            }
            // cout << tree.height << "[" << tree.scenic_score << "]" << " ";
        }
        // cout << endl;
    }
    cout <<  visible_count << endl;
    cout <<  max_scenic_score << endl;

}
