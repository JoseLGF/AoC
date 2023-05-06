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
#include <queue>
#include <climits>

#define CAVE_SMALL 0
#define CAVE_LARGE 1

struct Node
{
    int cost;
    int accum_cost;
    int x;
    int y;

    Node () {
        accum_cost = INT_MAX;
    }

    void init(int cost, int x, int y) {
        this->cost = cost;
        this->x = x;
        this->y = y;
    }

    // returns true if the cost was updated with a lower value
    bool update_accum_cost (int c) {
        if (c < accum_cost) {
            accum_cost = c;
            return true;
        }
        return false;
    }

    void set_as_initial() {
        accum_cost = 0;
    }

    void print() {
        std::cout
            << " x=" << x
            << " y=" << y
            << " c=" << cost
            << " ac=" << accum_cost
            << std::endl;
    }
};

class NodeComparator
{
    public:
    int operator() (const Node* n1, const Node* n2)
    {
        return n1->accum_cost > n2->accum_cost;
    }
};

class Maze
{
    // Risk levels of the initial tile
    std::vector<std::vector<int>> risk_levels;
    // Nodes for graph traversal
    std::vector<std::vector<Node>> nodes;
    // width and height of the tile
    int tile_width;
    int tile_height;
    // width and height of the cave
    int cave_width;
    int cave_height;
    // configuration to indicate if we are using the small or large maze
    int cave_size_config;

    public:
    Maze(std::vector<std::string> lines) {
        tile_height = lines.size();
        tile_width = lines[0].size();

        // Allocate risk levels
        for (int x=0; x<tile_width; x++) {
            risk_levels.push_back(
                    std::vector<int>(
                        tile_height));
        }
        // Populate risk levels
        for (int y=0; y<tile_height; y++) {
            for (int x=0; x<tile_width; x++) {
                risk_levels[x][y] = lines[y][x]-'0';
            }
        }
    }

    void set_cave_size(int size) {
        if ( (size != CAVE_SMALL) && (size != CAVE_LARGE)) {
            std::cout << "Error, wrong map size" << std::endl;
            return;
        }
        cave_size_config = size;
        if (size == CAVE_SMALL) {
            cave_height = tile_height;
            cave_width = tile_width;
        }
        if (size == CAVE_LARGE) {
            cave_height = tile_height * 5;
            cave_width = tile_width * 5;
        }
    }

    int calculate_node_risk(int x, int y) {
        int tile_x = x % tile_width;
        int tile_y = y % tile_height;
        int level = risk_levels[tile_x][tile_y];
        if (cave_size_config == CAVE_SMALL) {
            return level;
        }
        if (cave_size_config == CAVE_LARGE) {
            int x_offset = x / tile_width;
            int y_offset = y / tile_height;
            int new_level = level + x_offset + y_offset;
            // wrap around
            if (new_level > 9) {
                new_level =
                    ((new_level -1)
                     % 9)
                    + 1;
            }
            return new_level;
        }
        std::cout << "Error, maze not properly configured" << std::endl;
        return -1;
    }

    void generate_graph() {
        // clear any previous graph
        nodes.clear();

        // Allocate the nodes first
        for (int x=0; x<cave_width; x++) {
            nodes.push_back(
                    std::vector<Node>(
                        cave_height));
        }

        // Initialize them
        for (int y=0; y<cave_height; y++) {
            for (int x=0; x<cave_width; x++) {
                nodes[x][y].init(
                        calculate_node_risk(
                            x,
                            y),
                        x,
                        y);
            }
        }
    }

    void print_graph() {
        std::cout << "Maze nodes:" << std::endl;
        for (int y=0; y<cave_height; y++) {
            for (int x=0; x<cave_width; x++) {
                std::cout << nodes[x][y].cost;
            }
            std::cout << std::endl;
        }
    }

    void print_tile() {
        std::cout << "Maze tiles:" << std::endl;
        for (int y=0; y<tile_height; y++) {
            for (int x=0; x<tile_width; x++) {
                std::cout << risk_levels[x][y];
            }
            std::cout << std::endl;
        }
    }

    int find_lowest_risk_path() {
        nodes[0][0].set_as_initial();
        Node* initial_node = &nodes[0][0];
        std::priority_queue <Node*, std::vector<Node*>, NodeComparator > pq;

        // Add initial node
        pq.push(initial_node);
        // Node expansion loop
        while (not pq.empty()) {
            // Expand node with the minimum cost
            Node* current_node = pq.top();
            //std::cout << "Expanding: ";
            //current_node->print();
            pq.pop();
            // Check if node is target
            if (is_target(current_node)) {
                return current_node->accum_cost;
            }
            // expand current node
            std::vector<Node*> children = expand(current_node);
            // Add children to Q only if they have lower cost
            for (auto n: children) {
                //std::cout << "    Child:";
                //n->print();
                pq.push(n);
            }
        }
        // This should not be reached!
        return 0;
    }

    bool is_target(Node* node) {
        if (node->x == cave_width-1 &&
            node->y == cave_height-1)
        {
            return true;
        }
        return false;
    }

    std::vector<Node*> expand(Node* node) {
        std::vector<Node*> children;
        // Attempt expansion in the four directions
        int x = node->x;
        int new_x {};
        int y = node->y;
        int new_y {};
        int nac = node->accum_cost;
        int new_nac {};
        // up
        if (y>0) {
            new_x = x;
            new_y = y-1;
            new_nac = nac + nodes[new_x][new_y].cost;
            if (nodes[new_x][new_y].update_accum_cost(new_nac)) {
                children.push_back(&nodes[new_x][new_y]);
            }
        }
        // left
        if (x>0) {
            new_x = x-1;
            new_y = y;
            new_nac = nac + nodes[new_x][new_y].cost;
            if (nodes[new_x][new_y].update_accum_cost(new_nac)) {
                children.push_back(&nodes[new_x][new_y]);
            }
        }
        // down
        if (y<cave_height-1) {
            new_x = x;
            new_y = y+1;
            new_nac = nac + nodes[new_x][new_y].cost;
            if (nodes[new_x][new_y].update_accum_cost(new_nac)) {
                children.push_back(&nodes[new_x][new_y]);
            }
        }
        // right
        if (x<cave_width-1) {
            new_x = x+1;
            new_y = y;
            new_nac = nac + nodes[new_x][new_y].cost;
            if (nodes[new_x][new_y].update_accum_cost(new_nac)) {
                children.push_back(&nodes[new_x][new_y]);
            }
        }

        return children;
    }
};


void day15(std::string& input_path)
{
    int part_1_solution = -1;
    int part_2_solution = -1;
    std::ifstream infile(input_path);

    // Parse data
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    // Init
    Maze maze(lines);
    //maze.print_tile();

    // Part 1
    maze.set_cave_size(CAVE_SMALL);
    maze.generate_graph();
    //maze.print_graph();
    part_1_solution = maze.find_lowest_risk_path();

    // Part 2
    maze.set_cave_size(CAVE_LARGE);
    maze.generate_graph();
    //maze.print_graph();
    part_2_solution = maze.find_lowest_risk_path();

    // Display final results
    std::cout << "Day 15:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
