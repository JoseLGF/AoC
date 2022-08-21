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

enum CaveType
{
    Start_location = 0,
    End_location   = 1,
    Small_cave     = 2,
    Big_cave       = 3
};

struct Cave_Node
{
    std::string name;
    CaveType type;
    std::vector<Cave_Node*> connections;

    Cave_Node(std::string l_name) {
        name = l_name;
        if (name == "start") type = CaveType::Start_location;
        else if (name == "end") type = CaveType::End_location;
        else if (name[0] >= 'a' && name[0] <= 'z') type = CaveType::Small_cave;
        else if (name[0] >= 'A' && name[0] <= 'z') type = CaveType::Big_cave;
    }

    void display() {
        std::cout << name;
        switch(type) {
            case Start_location:
                std::cout << "(S)" << std::endl;
                break;
            case End_location:
                std::cout << "(E)" << std::endl;
                break;
            case Small_cave:
                std::cout << "(c)" << std::endl;
                break;
            case Big_cave:
                std::cout << "(C)" << std::endl;
                break;
        };
    }
};

class Path
{
    std::vector<Cave_Node*> path_nodes;
    bool has_small_cave_twice;
    Cave_Node* repeated;
    std::string repr;

    public:
    Path(Cave_Node* node) {
        repeated = nullptr;
        has_small_cave_twice = false;
        if (node->type != CaveType::Start_location) {
            std::cout << "Error, initial node must always be a start node" << std::endl;
            return;
        }
        path_nodes.push_back(node);
        repr += node->name + ",";
    }

    Path(Path* that, Cave_Node* last_node) {
        repeated = nullptr;
        has_small_cave_twice = false;
        //repeated = that->repeated;
        //has_small_cave_twice = that->has_small_cave_twice;
        for (auto pn: that->path_nodes) {
            add_node(pn);
        }
        add_node(last_node);
        repr = that->repr + last_node->name + ",";
    }

    void add_node(Cave_Node* node) {
        // Check if this node has been inserted before
        for (auto& p_node: path_nodes) {
            if ( (p_node->name == node->name) &&
                  p_node->type == CaveType::Small_cave) {
                has_small_cave_twice = true;
                repeated = node;
                break;
            }
        }
        path_nodes.push_back(node);
    }

    bool is_complete() {
        // The path is complete when it starts in the Start node and
        // ends in an End node
        if (path_nodes.front()->type == CaveType::Start_location) {
            if (path_nodes.back()->type == CaveType::End_location) {
                return true;
            }
        }
        return false;
    }

    std::vector<Path> expand_first_policy() {
        std::vector<Path> children {};
        Cave_Node* current_location = path_nodes.back();
        std::vector<Cave_Node*> possible_connections {};
        // Check all places we can visit from the path's last node
        std::vector<Cave_Node*> connections = current_location->connections;
        for (auto connection : connections) {
            // Discard Start location
            if (connection->type == CaveType::Start_location) {
                continue; // discard
            }
            // Discard small caves if they have already been visited
            if (connection->type == CaveType::Small_cave) {
                // check if already visited
                if (has_been_visited(connection)) {
                    continue;
                }
            }
            // Add this connection to the children
            possible_connections.push_back(connection);
        }
        // Make new paths with the possible connections
        for (auto pc: possible_connections) {
            children.push_back(Path(this, pc));
        }
        return children;
    }

    std::vector<Path> expand_second_policy() {
        std::vector<Path> children {};
        Cave_Node* current_location = path_nodes.back();
        std::vector<Cave_Node*> possible_connections {};
        // Check all places we can visit from the path's last node
        std::vector<Cave_Node*> connections = current_location->connections;
        for (auto connection : connections) {
            // Discard Start location
            if (connection->type == CaveType::Start_location) {
                continue; // discard
            }
            // Discard small caves if they have already been visited
            if (connection->type == CaveType::Small_cave) {
                // Check if we have visited a small cave twice
                if (has_small_cave_twice) {
                    // check if already visited
                    if (has_been_visited(connection)) {
                        continue;
                    }
                }
            }
            // Add this connection to the children
            possible_connections.push_back(connection);
        }
        // Make new paths with the possible connections
        for (auto pc: possible_connections) {
            children.push_back(Path(this, pc));
        }
        return children;
    }

    bool has_been_visited(Cave_Node* node) {
        for (auto previous_node : path_nodes) {
            if (previous_node == node) {
                return true;
            }
        }
        return false;
    }

    void display() {
        for (auto& node: path_nodes) {
            std:: cout << node->name << "->";
        }
            std:: cout << std::endl;
    }
};

class Cave_Network
{
    std::vector<Cave_Node> nodes;
    Cave_Node* start_node;
    Cave_Node* end_node;
    std::vector<Path> complete_paths;

public:
    // The network can be initialized from a vector of strings
    Cave_Network(std::vector<std::string> tokens) {
        for (auto t: tokens) {
            nodes.push_back(t);
        }

        for (auto& n: nodes) {
            if (n.type == CaveType::Start_location) {
                start_node = &n;
            }
            if (n.type == CaveType::End_location) {
                end_node = &n;
            }
        }
    }

    void display() {
        std::cout << "Network:" << std::endl;
        for (auto n: nodes) {
            n.display();
            for (auto ref: n.connections) {
                std::cout << "-->" << ref->name << std::endl;
            }
        }
    }

    void add_connection(std::string name1, std::string name2) {
        Cave_Node* ref_node1 = get_node_ref_by_name(name1);
        Cave_Node* ref_node2 = get_node_ref_by_name(name2);
        if (ref_node1 == nullptr || ref_node2 == nullptr) {
            std::cout << "Error adding connection to empty node" << std::endl;
            return;
        }
        // Connection should be bidirectional
        ref_node1->connections.push_back(ref_node2);
        ref_node2->connections.push_back(ref_node1);
    }

    Cave_Node* get_node_ref_by_name(std::string name) {
        for (auto& node: nodes) {
            if (node.name == name) {
                return &node;
            }
        }
        std::cout << "Node not found for the given name " << name << std::endl;
        return nullptr;
    }

    int find_paths(int policy_number) {
        complete_paths.clear();
        std::vector<Path> current_paths;
        // Create the initial path
        current_paths.push_back(Path(start_node));

        while(! current_paths.empty() ) {
            Path current_path = current_paths.back();
            std::vector<Path> children;
            current_paths.pop_back();
            // Expand the current path
            if (policy_number == 1) {
                children = current_path.expand_first_policy();
            }
            if (policy_number == 2) {
                children = current_path.expand_second_policy();
            }
            // From the children, separate complete paths and current
            // paths
            for (auto& path: children) {
                if (path.is_complete()) {
                    complete_paths.push_back(path);
                }
                else {
                    current_paths.push_back(path);
                }
            }
        }
        return complete_paths.size();

    }

    void display_complete_paths() {
        for (auto& path: complete_paths) {
            path.display();
        }
            std:: cout << std::endl;
    }

};


void day12()
{
    int part_1_solution = -1;
    int part_2_solution = -1;
    std::ifstream infile("input/day12.txt");

    // Parse data
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    // Init
    // Find all tokens in the input
    std::vector<std::string> tokens;
    std::string token;
    for (auto l: lines) {
        std::stringstream sl(l);
        while(getline(sl, token, '-')) {
            tokens.push_back(token);
        }
    }
    // Remove duplicates
    std::set<std::string> s_tokens( tokens.begin(), tokens.end() );
    tokens.assign( s_tokens.begin(), s_tokens.end() );
    // Build the network
    Cave_Network network(tokens);
    for (auto l: lines) {
        std::stringstream sl(l);
        std::string source;
        std::string target;
        getline(sl, source, '-');
        getline(sl, target, '-');
        network.add_connection(source, target);
    }

    // Part 1
    part_1_solution = network.find_paths(1);

    // Part 2
    part_2_solution = network.find_paths(2);
    //network.display_complete_paths();

    // Display final results
    std::cout << "Day 12:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
