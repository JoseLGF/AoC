#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>


struct Board
{
    int grid[5][5];
    bool marked[5][5];
    bool isWinner;
    int lastNumber;

    bool checkWinner () { return isWinner; }

    int getScore() {
        int sum_unmarked_squares = 0;
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                if (not marked[i][j]) {
                    sum_unmarked_squares += grid[i][j];
                }
            }
        }
        return lastNumber * sum_unmarked_squares;
    }

    Board(std::vector<int> nums, int begin) {
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                grid[i][j] = nums[begin + i*5 + j];
                marked[i][j] = false;
            }
        }
    }

    void print() {
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    bool checkWinningCondition() {
        unsigned char r0 {}, c0 {};
        unsigned char r1 {}, c1 {};
        unsigned char r2 {}, c2 {};
        unsigned char r3 {}, c3 {};
        unsigned char r4 {}, c4 {};

        if(marked[0][0]) { r0++; c0++; }
        if(marked[0][1]) { r0++; c1++; }
        if(marked[0][2]) { r0++; c2++; }
        if(marked[0][3]) { r0++; c3++; }
        if(marked[0][4]) { r0++; c4++; }
        if(marked[1][0]) { r1++; c0++; }
        if(marked[1][1]) { r1++; c1++; }
        if(marked[1][2]) { r1++; c2++; }
        if(marked[1][3]) { r1++; c3++; }
        if(marked[1][4]) { r1++; c4++; }
        if(marked[2][0]) { r2++; c0++; }
        if(marked[2][1]) { r2++; c1++; }
        if(marked[2][2]) { r2++; c2++; }
        if(marked[2][3]) { r2++; c3++; }
        if(marked[2][4]) { r2++; c4++; }
        if(marked[3][0]) { r3++; c0++; }
        if(marked[3][1]) { r3++; c1++; }
        if(marked[3][2]) { r3++; c2++; }
        if(marked[3][3]) { r3++; c3++; }
        if(marked[3][4]) { r3++; c4++; }
        if(marked[4][0]) { r4++; c0++; }
        if(marked[4][1]) { r4++; c1++; }
        if(marked[4][2]) { r4++; c2++; }
        if(marked[4][3]) { r4++; c3++; }
        if(marked[4][4]) { r4++; c4++; }

        if ( r0 > 4 || c0 > 4 ||
             r1 > 4 || c1 > 4 ||
             r2 > 4 || c2 > 4 ||
             r3 > 4 || c3 > 4 ||
             r4 > 4 || c4 > 4 )
        {
            return true;
        }

        return false;
    }

    void check_number (int n) {
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                if (grid[i][j] == n) {
                    marked[i][j] = true;
                    if (checkWinningCondition()) {
                        isWinner = true;
                        lastNumber = n;
                        return;
                    }
                }
            }
        }
    }

};

std::vector<int> get_random_order(std::string str_order)
{
    std::vector<int> vect;
    std::stringstream ss(str_order);

    for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    return vect;
}

void day04()
{
    std::ifstream infile("input/day04.txt");

    // Get the random order
    std::string str_order;
    std::string board1;
    infile >> str_order;
    std::vector<int> random_order = get_random_order(str_order);

    // Get the boards
    std::vector<int> boards_numbers;
    int current_number;
    while (infile >> current_number)
        boards_numbers.push_back(current_number);

    // Group the numbers into board data structures
    std::vector<Board> boards;
    for (int i=0; i<boards_numbers.size()/25; i++) {
        boards.push_back(Board(boards_numbers, 25*i));
    }

    // Capture all winning numbers in the order in which they win
    std::vector<int> winning_numbers;

    // Simulate game
    for (auto n : random_order) {
        for (auto& board: boards) {
            if (!board.checkWinner()) {
                board.check_number(n);
                if (board.checkWinner())
                    winning_numbers.push_back(board.getScore());
            }
        }
    }

    // Display final results
    std::cout << "Day 4:" << std::endl;
    std::cout << winning_numbers.front() << std::endl;
    std::cout << winning_numbers.back() << std::endl;
}
