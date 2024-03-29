#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

//#define TESTING

#pragma region BASIC NODE OPERATIONS

struct
BNode
{
    BNode* left_child;
    BNode* right_child;
    BNode* parent;
    int value;

    BNode()
    {
        this->left_child = nullptr;
        this->right_child = nullptr;
        this->parent = nullptr;
        this->value = -1;
    }

    BNode(BNode* parent)
    {
        this->left_child = nullptr;
        this->right_child = nullptr;
        this->parent = parent;
        this->value = -1;
    }
};

bool
is_leaf_node(BNode* node)
{
    return(
        (node->left_child == nullptr) &&
        (node->right_child == nullptr));
}

bool
is_pair_node(BNode* node)
{
    return (
        (node->left_child != nullptr) ||
        (node->right_child != nullptr));
}

int
nest_level(BNode* node, int level=0)
{
    if(node->parent == nullptr) {
        return level;
    }
    return nest_level(node->parent, level+1);
}

#pragma endregion

#pragma region BASIC TREE OPERATIONS

void
make_tree(std::stringstream& str, BNode* parent)
{
    char c;
    str >> c;
    if (c >= '0' && c <= '9') {
        parent->value = c - '0';
        return;
    }

    if('[' == c) {
        parent->left_child = new BNode(parent);
        make_tree(str, parent->left_child);
        str >> c; // consume ','
        parent->right_child = new BNode(parent);
        make_tree(str, parent->right_child);
        str >> c; // consume ']'
    }
}

void
copy_tree(BNode* source, BNode* target)
{
    target->value = source->value;

    if(source->left_child != nullptr) {
        target->left_child = new BNode(target);
        copy_tree(source->left_child, target->left_child);
    }

    if(source->right_child != nullptr) {
        target->right_child = new BNode(target);
        copy_tree(source->right_child, target->right_child);
    }
}

void
delete_tree(BNode* node)
{
    if (node == nullptr) {
        return;
    }

    if (node->left_child != nullptr) {
        delete_tree(node->left_child);
    }
    if (node->right_child != nullptr) {
        delete_tree(node->right_child);
    }

    delete node;
}

void
delete_subtree(BNode* node)
{
    // Deletes all nodes below input node,
    delete_tree(node->left_child);
    delete_tree(node->right_child);
}

void
replace_node_with_value(BNode* node, int value)
{
    delete_tree(node->left_child);
    delete_tree(node->right_child);
    node->left_child = nullptr;
    node->right_child = nullptr;
    node->value = value;
}

void
replace_node_with_pair(BNode* node, int left_value, int right_value)
{
    delete_tree(node->left_child);
    delete_tree(node->right_child);
    node->left_child = new BNode(node);
    node->left_child->value = left_value;
    node->right_child = new BNode(node);
    node->right_child->value = right_value;
    node->value = -1;
}

#pragma endregion

#pragma region FUNCTORS AND OPERATIONS FOR TRAVERSING TREES

template <typename T>
struct
accumulate_functor
{
    std::vector<T> elements;

    void operator() (T e) {
        elements.push_back(e);
    }
};

template <typename Functor>
void
preorder_traverse(BNode* node, Functor& fun)
{
    if (node->left_child != nullptr) {
        preorder_traverse(node->left_child, fun);
    }

    fun(node);

    if (node->right_child != nullptr) {
        preorder_traverse(node->right_child, fun);
    }
}

template <typename Functor>
void
apply_on_leaves(BNode* node, Functor& fun)
{
    if (node->left_child != nullptr) {
        apply_on_leaves(node->left_child, fun);
    }

    if (is_leaf_node(node)) {
        fun(node);
        return;
    }

    if (node->right_child != nullptr) {
        apply_on_leaves(node->right_child, fun);
    }
}

template <typename Functor>
void
apply_on_pair_nodes(BNode* node, Functor& fun)
{

    if (node->left_child != nullptr) {
        apply_on_pair_nodes(node->left_child, fun);
    }

    if (is_pair_node(node)) {
        fun(node);
    }

    if (node->right_child != nullptr) {
        apply_on_pair_nodes(node->right_child, fun);
    }
}

std::vector<BNode*>
make_tree_as_array(BNode* root_node)
{
    accumulate_functor<BNode*> af;
    preorder_traverse(root_node, af);
    return af.elements;
}

std::vector<BNode*>
make_tree_pairs_as_array(BNode* root_node)
{
    accumulate_functor<BNode*> af;
    apply_on_pair_nodes(root_node, af);
    return af.elements;
}

std::vector<BNode*>
make_tree_leaves_array(BNode* root_node)
{
    accumulate_functor<BNode*> af;
    apply_on_leaves(root_node, af);
    return af.elements;
}

BNode*
next_leaf_in_array(std::vector<BNode*> tree_array, BNode* node)
{
    auto it = std::find(tree_array.begin(), tree_array.end(), node);

    if (
        (it == tree_array.end()) ||
        (it == tree_array.end()-1)
        ) {
        return nullptr;
    }
    
    return *(it+1);
}

BNode*
prev_leaf_in_array(std::vector<BNode*> tree_array, BNode* node)
{
    auto it = std::find(tree_array.begin(), tree_array.end(), node);

    if (
        (it == tree_array.end()) ||
        (it == tree_array.begin())
        ) {
        return nullptr;
    }
    
    return *(it-1);
}

#pragma endregion

#pragma region OPERATIONS FOR SNAILNUMBERS

BNode*
make_snail_number(std::string str)
{
    std::stringstream stream{str};
    BNode* out = new BNode();
    make_tree(stream, out);
    return out;
}

void
print_snail_number(BNode* root_node)
{
    if (is_leaf_node(root_node)) {
        std::cout << root_node->value;
        
    }
    else {
        if (root_node->left_child != nullptr) {
            std::cout << "[";
            print_snail_number(root_node->left_child);
        }
        
        std::cout << ',';
        
        if (root_node->right_child != nullptr) {
            print_snail_number(root_node->right_child);
        }
        std::cout << "]";
    }
}

BNode*
find_pair_nested_4(BNode* root_node)
{
    // Find and return the leftmost node in a tree with nest level 4.
    // If no such node is present return nullptr
    auto tree_pairs_array = make_tree_pairs_as_array(root_node);
    for (auto node: tree_pairs_array) {
        if (nest_level(node) == 4) {
            return node;
        }
    }

    return nullptr;
}

bool
explode_once(BNode* root_node)
{
    // Find a pair with nesting level 4 to explode it
    auto x_node = find_pair_nested_4(root_node);
    if (x_node == nullptr) {
        // Didnt find a node to explode
        return false;
    }

    // found a node to explode
    auto leaf_array = make_tree_leaves_array(root_node);

    // Left operation
    auto left_from_xnode = prev_leaf_in_array(leaf_array, x_node->left_child);
    if(left_from_xnode != nullptr) {
        left_from_xnode->value += x_node->left_child->value;
    }

    // Right operation
    auto right_from_xnode = next_leaf_in_array(leaf_array, x_node->right_child);
    if(right_from_xnode != nullptr) {
        right_from_xnode->value += x_node->right_child->value;
    }

    replace_node_with_value(x_node, 0);

    return true;
}

bool
split_once(BNode* root_node)
{
    auto leaf_array = make_tree_leaves_array(root_node);

    for (auto leaf_node: leaf_array) {
        if (leaf_node->value >= 10) {
            replace_node_with_pair(
                leaf_node,
                floor(leaf_node->value / 2.0),
                ceil(leaf_node->value / 2.0));
            return true;
        }
    }
    return false;
}

void
reduce_snail_number(BNode* root_node)
{
    if(explode_once(root_node)) {
        reduce_snail_number(root_node);
        return;
    }
    else if (split_once(root_node)) {
        reduce_snail_number(root_node);
        return;
    }
}

BNode*
add_snail_numbers(BNode* left, BNode* right)
{
    BNode* left_copy = new BNode();
    copy_tree(left, left_copy);
    BNode* right_copy = new BNode();
    copy_tree(right, right_copy);
    BNode* result = new BNode();
    result->left_child = left_copy;
    result->left_child->parent = result;
    result->right_child = right_copy;
    result->right_child->parent = result;

    reduce_snail_number(result);

    return result;
}

int
magnitude_of_snail_number(BNode* node)
{
    if (is_leaf_node(node)) {
        return node->value;
    }
    // It is guaranteed that all non-leaf nodes are always pairs
    return (
        3 * magnitude_of_snail_number(node->left_child) +
        2 * magnitude_of_snail_number(node->right_child)
    );

}

#pragma endregion

#pragma region DRIVER CODE

#ifdef TESTING

void
day18()
{
    // Make new snail numbers based on a string
    auto a = make_snail_number("[1,2]");
    auto b = make_snail_number("[[1,2],3]");

    // Print the snail number, generating the same string to create it
    print_snail_number(b);
    std::cout << std::endl;

    // Copy a number to prevent the changes in one to affect changes in other
    auto c = new BNode();
    copy_tree(b, c);
    delete b;
    print_snail_number(c);
    std::cout << std::endl;

    // Add snail numbers, combining them into a new number
    auto n1 = make_snail_number("[1,2]");
    auto n2 = make_snail_number("[[3,4],5]");
    auto n3 = add_snail_numbers(n1, n2);
    print_snail_number(n3);
    std::cout << std::endl;

    // Find pair with nest level 4 for exploding
    std::cout << "Next" << std::endl;
    auto nl4 = make_snail_number("[[[[[9,8],1],2],3],4]");
    auto nl5 = make_snail_number("[7,[6,[5,[4,[3,2]]]]]");
    
    auto node_4 = find_pair_nested_4(nl5);
    if (node_4 != nullptr) {
        std::cout   << node_4->left_child->value
                    << "," << node_4->right_child->value
                    << std::endl;
    }

    // Explode functionality
    std::cout << "Exploding a snail number" << std::endl;
    auto e1 = make_snail_number("[[[[[9,8],1],2],3],4]");
    explode_once(e1);
    print_snail_number(e1);

    std::cout << "Exploding a snail number" << std::endl;
    auto e2 = make_snail_number("[7,[6,[5,[4,[3,2]]]]]");
    explode_once(e2);
    print_snail_number(e2);

    std::cout << "Exploding a snail number" << std::endl;
    auto e3 = make_snail_number("[[6,[5,[4,[3,2]]]],1]");
    explode_once(e3);
    print_snail_number(e3);

    std::cout << "Exploding a snail number" << std::endl;
    auto e4 = make_snail_number("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]");
    explode_once(e4);
    print_snail_number(e4);

    std::cout << "Exploding a snail number" << std::endl;
    auto e5 = make_snail_number("[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]");
    explode_once(e5);
    print_snail_number(e5);

    // Split and explode functionality
    auto se1 = make_snail_number("[[[[4,3],4],4],[7,[[8,4],9]]]");
    auto se2 = make_snail_number("[1,1]");
    std::cout << "After addition" << std::endl;
    auto se3 = add_snail_numbers(se1, se2);
    print_snail_number(se3);
    std::cout << "After explode" << std::endl;
    explode_once(se3);
    print_snail_number(se3);
    std::cout << "After explode" << std::endl;
    explode_once(se3);
    print_snail_number(se3);
    std::cout << "After split" << std::endl;
    split_once(se3);
    print_snail_number(se3);
    std::cout << "After split" << std::endl;
    split_once(se3);
    print_snail_number(se3);
    std::cout << "After explode" << std::endl;
    explode_once(se3);
    print_snail_number(se3);

    // Reduction functionality
    std::cout << "Reduction" << std::endl;
    auto r1 = make_snail_number("[[[[4,3],4],4],[7,[[8,4],9]]]");
    auto r2 = make_snail_number("[1,1]");
    std::cout << "After reduction" << std::endl;
    auto r3 = add_snail_numbers(r1, r2);
    reduce_snail_number(r3);
    print_snail_number(r3);

    // Full addition functionality
    std::cout << "Addition functionality:" << std::endl;
    auto a1 = make_snail_number("[[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]");
    auto a2 = make_snail_number("[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]");
    auto a3 = add_snail_numbers_without_reduce(a1, a2);
    std::cout << "Number to reduce:" << std::endl;
    print_snail_number(a3);
    reduce_snail_number(a3);

    // Check magnitude calculation
    std::cout << "Magnitude calculations:" << std::endl;
    auto m1 = make_snail_number("[[1,2],[[3,4],5]]");
    auto m2 = make_snail_number("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]");
    auto m3 = make_snail_number("[[[[1,1],[2,2]],[3,3]],[4,4]]");
    auto m4 = make_snail_number("[[[[3,0],[5,3]],[4,4]],[5,5]]");
    auto m5 = make_snail_number("[[[[5,0],[7,4]],[5,5]],[6,6]]");
    auto m6 = make_snail_number("[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]");

    std::cout << magnitude_of_snail_number(m1) << std::endl;
    std::cout << magnitude_of_snail_number(m2) << std::endl;
    std::cout << magnitude_of_snail_number(m3) << std::endl;
    std::cout << magnitude_of_snail_number(m4) << std::endl;
    std::cout << magnitude_of_snail_number(m5) << std::endl;
    std::cout << magnitude_of_snail_number(m6) << std::endl;

}

#endif

#pragma endregion

#pragma region DAY 18 CODE
#ifndef TESTING
void
day18(std::string& input_path)
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
    auto num = make_snail_number(lines[0]);
    for (int i=1; i<lines.size(); i++) {
        num = add_snail_numbers(
                num,
                make_snail_number(lines[i]));
        
    }

    // Part 1
    part_1_solution = magnitude_of_snail_number(num);

    // Part 2
    int max_magnitude = -1;
    for (int i=0; i<lines.size(); i++) {
        for (int j=0; j<lines.size(); j++) {
            auto left = make_snail_number(lines[i]);
            auto right = make_snail_number(lines[j]);
            auto sum = add_snail_numbers(left, right);
            auto magnitude = magnitude_of_snail_number(sum);
            if (magnitude > max_magnitude) {
                max_magnitude = magnitude;
            }
        }
    }
    part_2_solution = max_magnitude;

    // Display final results
    std::cout << "Day 18:" << std::endl;
    std::cout << part_1_solution << std::endl;
    std::cout << part_2_solution << std::endl;
}
#endif
#pragma endregion