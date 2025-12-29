#include "common.h"

#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <cstdint>

using namespace std;

namespace {
	const bool test_input = false;
	const int day = 7;
	vector<string> input;
	vector<string> grid;
	u32 numBeamSplits = 0;
	u64 timelines = 0;
	vector<vector<u64>> memo;

	void Initialize() {
		static bool initialized = false;
		if (initialized) return;

		input = get_input(day, test_input);
		initialized = true;

		// the same calculation solves part 1 and 2
		grid = input;

		for (int i = 0; i < grid.size(); i++) {
			memo.push_back({});
			for (int j = 0; j < grid[0].size(); j++) {
				memo[i].push_back(0);
			}
		}

		for (int y = 0; y < grid.size(); y++) {
			for (int x = 0; x < grid[0].size(); x++) {
				char c = grid[y][x];
				if (c == 'S') {
					// place beam below starting point
					grid[y + 1][x] = '|';
					memo[y + 1][x] = 1;
				}
				else if (c == '^') {
					// check if there is a beam above the splitter
					if (grid[y - 1][x] == '|') {
						// beam is split
						numBeamSplits++;
						grid[y][x - 1] = '|';
						grid[y][x + 1] = '|';
						memo[y][x - 1] += memo[y - 1][x];
						memo[y][x + 1] += memo[y - 1][x];
					}
				}
				else if (c == '.') {
					// if there is a beam above
					if (y > 0 && (grid[y - 1][x] == '|')) {
						// propagate beam downwards
						grid[y][x] = '|';
						memo[y][x] = memo[y - 1][x];
					}
				}
				else if (c == '|') {
					memo[y][x] += memo[y - 1][x];
				}
			}
		}
	}
}

namespace aoc2025::day07 {
	void part1() {
		Initialize();

		cout << numBeamSplits << endl;
	}

	void part2() {
		Initialize();

		auto lastLine = memo.back();

		for (auto n : lastLine) {
			timelines += n;
		}
		cout << timelines << endl;
	}
}
