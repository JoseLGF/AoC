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
#include <queue>
#include <unordered_set>

struct Point
{
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}
};


int calculate_basin_size(const std::vector<std::string>& map, Point location)
{
    int size = 0;
    int map_height = map.size();
    int map_width = map[0].size();

    // keep track of which nodes have been expanded
    std::vector<bool> expanded_nodes (map_height * map_width, false);

    // The nodes that we want to expand next
    std::vector<Point> expand_queue;

    // Initialize the algorithm
    expand_queue.push_back(location);
    //expanded_nodes[map_width*location.y + location.x] = true;

    // Node expansion
    while (!expand_queue.empty()) {
        // Select current node
        Point current_node = expand_queue.back();
        expand_queue.pop_back();
        // Check if the current node is good
        int x = current_node.x;
        int y = current_node.y;
        if (x < 0) continue;
        if (y < 0) continue;
        if (x >= map_width) continue;
        if (y >= map_height) continue;
        if (map[y][x] == '9') continue;
        if (expanded_nodes[map_width*y+x]) continue;

        // Node is good, add to size and expand
        size++;
        expand_queue.push_back(Point(x-1, y  ));
        expand_queue.push_back(Point(x+1, y  ));
        expand_queue.push_back(Point(x  , y-1));
        expand_queue.push_back(Point(x  , y+1));
        expanded_nodes[map_width*y + x] = true;
    }
    return size;
}

void day09(std::string& input_path)
{
    int part_1_solution = -1;
    int part_2_solution = -1;
    std::ifstream infile(input_path);

    // Low points are calculated in part 1, and required for part 2
    std::vector<Point> low_points;

    // Parse data
    std::string line;
    std::string token;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    // Part 1 - Find low points
    int height = lines.size();
    int width = lines[0].size();
    int sum_of_risks = 0;
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            bool left_is_higher = false;
            bool right_is_higher = false;
            bool up_is_higher = false;
            bool down_is_higher = false;

            if ( (0 == x) || (lines[y][x-1] > lines[y][x])) {
                left_is_higher = true;
            }
            if ( (width-1 == x) || (lines[y][x+1] > lines[y][x])) {
                right_is_higher = true;
            }
            if ( (0 == y) || (lines[y-1][x] > lines[y][x])) {
                up_is_higher = true;
            }
            if ( (height-1 == y) || (lines[y+1][x] > lines[y][x])) {
                down_is_higher = true;
            }

            if (left_is_higher && right_is_higher && up_is_higher && down_is_higher) {
                low_points.push_back(Point(x, y));
                sum_of_risks += 1 + lines[y][x] - '0';
            }

        }
    }
    part_1_solution = sum_of_risks;

    // Part 2 - Find largest basins
    std::vector<int> basin_sizes;
    // Calculate each low_point's associated basin
    for (auto p: low_points) {
        // Get neighbors
        basin_sizes.push_back(calculate_basin_size(lines, p));
    }
    // Sort to get the largest 3 basins
    std::sort(basin_sizes.begin(), basin_sizes.end(), std::greater<>());
    // Multiply the sizes of the three largest basins
    if (basin_sizes.size() > 2) {
        part_2_solution = basin_sizes[0] *
                          basin_sizes[1] *
                          basin_sizes[2];
    }


    // Display final results
    std::cout << "Day 9:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
