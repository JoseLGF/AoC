#include "common.h"
#include "logger.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

namespace {
	Logger logger("Day1");
	vector<string> input;
}

namespace aoc2025::day01 {
	void part1() {
		int dial_rotation = 50;
		int zero_count = 0;

		input = get_input(1);

		for (const auto& line : input) {
			stringstream ss(line);
			char dir;
			int amount;
			ss >> dir;
			ss >> amount;
			logger.info("Rotate " + to_string(dir) + " by " + to_string(amount));

			if (dir == 'L') {
				dial_rotation -= (amount % 100);
				if (dial_rotation < 0) {
					dial_rotation = 100 + dial_rotation;
				}
			}
			else {
				dial_rotation += (amount % 100);
				if (dial_rotation > 99) {
					dial_rotation = dial_rotation - 100;
				}
			}
			logger.info("Points at " + to_string(dial_rotation));

			if (dial_rotation == 0) {
				zero_count++;
			}
		}

		cout << zero_count << endl;

	}

	void part2() {
		int dial_rotation = 50;
		int zero_crossings = 0;

		for (const auto& line : input) {
			stringstream ss(line);
			char dir;
			int amount;
			ss >> dir;
			ss >> amount;

			for (int i=0; i < amount; i++) {
				if (dir == 'L') {
					if (dial_rotation == 0) {
						dial_rotation = 99;
					}
					else {
						dial_rotation--;
					}
				}
				else {
					if (dial_rotation == 99) {
						dial_rotation = 0;
					}
					else {
						dial_rotation++;
					}
				}
				if (dial_rotation == 0) {
					zero_crossings++;
				}
			}
		}

		cout << zero_crossings << endl;

	}
}