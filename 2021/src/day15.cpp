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
    std::vector<std::vector<Node>> nodes;
    int width;
    int height;

    public:
    Maze(std::vector<std::string> lines) {
        height = lines.size();
        width = lines[0].size();

        // Allocate the nodes first
        for (int x=0; x<width; x++) {
            nodes.push_back(std::vector<Node>(height));
        }

        // Initialize them
        for (int y=0; y<height; y++) {
            for (int x=0; x<width; x++) {
                nodes[x][y].init(lines[y][x]-'0', x, y);
            }
        }
    }

    void print() {
        for (auto row: nodes) {
            for (auto node: row) {
                std::cout << node.cost;
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
            std::cout << "Expanding: ";
            current_node->print();
            pq.pop();
            // Check if node is target
            if (is_target(current_node)) {
                return current_node->accum_cost;
            }
            // expand current node
            std::vector<Node*> children = expand(current_node);
            // Add children to Q only if they have lower cost
            for (auto n: children) {
                std::cout << "    Child:";
                n->print();
                pq.push(n);
            }
        }
        // This should not be reached!
        return 0;
    }

    bool is_target(Node* node) {
        if (node->x == width-1 &&
            node->y == height-1)
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
        if (y<height-1) {
            new_x = x;
            new_y = y+1;
            new_nac = nac + nodes[new_x][new_y].cost;
            if (nodes[new_x][new_y].update_accum_cost(new_nac)) {
                children.push_back(&nodes[new_x][new_y]);
            }
        }
        // right
        if (x<width-1) {
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


void day15()
{
    int part_1_solution = -1;
    int part_2_solution = -1;
    std::ifstream infile("input/day15.txt");

    // Parse data
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    // Init
    for (auto line: lines) {
        std::cout << line << std::endl;
    }
    Maze maze(lines);
    std::cout << "Maze:" << std::endl;
    maze.print();

    // Part 1
    part_1_solution = maze.find_lowest_risk_path();

    // Part 2

    // Display final results
    std::cout << "Day 15:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
