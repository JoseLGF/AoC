#include "common.h"
#include "logger.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

namespace {
	Logger logger("Day4");
	vector<string> input;
}

namespace aoc2025::day04 {
	struct Cell {
		int x;
		int y;
	};

	vector<Cell> FindAccessibleRolls(const vector<string>& grid) {
		vector<Cell> accessibleRollsPositions;
		int width = grid[0].size();
		int height = grid.size();
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				auto cell = grid[y][x];
				if (cell == '@') {
					// check neighbors
					int adjacentRolls = 0;
					/* up    */ if (y > 0 && (grid[y - 1][x] == '@')) { adjacentRolls++; }
					/* down  */ if (y < (height - 1) && (grid[y + 1][x] == '@')) { adjacentRolls++; }
					/* left  */ if (x > 0 && (grid[y][x - 1] == '@')) { adjacentRolls++; }
					/* right */ if (x < (width - 1) && (grid[y][x + 1] == '@')) { adjacentRolls++; }

					/* up-left    */ if ((y > 0) && (x > 0) && (grid[y - 1][x - 1] == '@')) { adjacentRolls++; }
					/* up-right   */ if ((y > 0) && (x < (width - 1)) && (grid[y - 1][x + 1] == '@')) { adjacentRolls++; }
					/* down-left  */ if ((y < (height - 1)) && (x > 0) && (grid[y + 1][x - 1] == '@')) { adjacentRolls++; }
					/* down-right */ if ((y < (height - 1)) && (x < (width - 1)) && (grid[y + 1][x + 1] == '@')) { adjacentRolls++; }
					if (adjacentRolls < 4) { accessibleRollsPositions.push_back(Cell{.x = x, .y = y}); }
				}
			}
		}
		return accessibleRollsPositions;
	}

	void part1() {
		input = get_input(4, false);

		int accessibleRolls = FindAccessibleRolls(input).size();
		
		cout << accessibleRolls << endl;
	}

	void part2() {

		int accessibleRolls = 0;
		int totalNumAccessibleRolls = 0;
		do {
			auto accessibleRollsPositions = FindAccessibleRolls(input);
			accessibleRolls = accessibleRollsPositions.size();
			totalNumAccessibleRolls += accessibleRolls;

			for (const auto& position : accessibleRollsPositions) {
				input[position.y][position.x] = '.';
			}
		} while (accessibleRolls > 0);

		cout << totalNumAccessibleRolls << endl;
	}
}
