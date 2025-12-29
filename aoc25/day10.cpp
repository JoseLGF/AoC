#include "common.h"
#include "logger.h"

#include <iostream>
#include <tuple>
#include <sstream>
#include <cstdlib>
#include <regex>

using namespace std;

namespace {
	Logger logger("Day10", true);
	const bool test_input = true;
	const int day = 10;
	vector<string> input;

	vector<tuple<int, int>> redTiles;

	void Initialize() {
		static bool initialized = false;
		if (initialized) return;

		input = get_input(day, test_input);
		initialized = true;
	}

	vector<bool> parseLights(const string& lights) {
		vector<bool> out;
		for (const auto c : lights) {
			out.push_back((c == '#') ? true : false);
		}
		return out;
	}

	vector<vector<int>> parseButtons(const string& buttons) {
		vector<vector<int>> out;

		const auto buttonsLists = split_line(buttons, ' ');

		for (const auto& buttonsList : buttonsLists) {
			stringstream ss(buttonsList);

		}

		return out;
	}

	u64 calculateMinButtonPresses(const string& lights, const string& buttons) {
		return 0;
	}
}

namespace aoc2025::day10 {
	void part1() {
		Initialize();

		const regex pattern("\\[(.+)\\] (\\(.+\\)) (\\{.+\\})");

		u64 buttonPresses = 0;
		for (const auto& line : input) {
			smatch matches;
			if (regex_search(line, matches, pattern)) {
				auto& lights = matches[1];
				auto& buttons = matches[2];

				buttonPresses += calculateMinButtonPresses(lights, buttons);
				logger.info("Lights: " + string(matches[1])); // First capture group
				logger.info("Buttons: " + string(matches[2])); // Second capture group
			}
			else {
				std::cout << "No match found.\n";
			}
		}

		cout << buttonPresses << endl;
	}

	void part2() {
		Initialize();
	}
}
