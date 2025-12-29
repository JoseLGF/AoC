#include "common.h"
#include "logger.h"

#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <cstdint>

using namespace std;

namespace {
	Logger logger("Day6");
	const bool test_input = false;
	vector<string> input;

	void Initialize() {
		static bool initialized = false;
		if (initialized) return;

		input = get_input(6, test_input);
		initialized = true;
	}
}

namespace aoc2025::day06 {
	void part1() {
		Initialize();

		vector<vector<string>> tokens_dd;
		for (const auto& line : input) {
			tokens_dd.push_back({});
			auto tokens = split_line(line, ' ');

			for (auto token : tokens) {
				if (!token.empty()) {
					tokens_dd.back().push_back(token);
				}
			}
		}

		u64 grandTotal = 0;
		for (int col = 0; col < tokens_dd[0].size(); col++) {
			auto op = tokens_dd[tokens_dd.size() - 1][col];
			if (op == "+") {
				u64 sum = 0;
				for (int row = 0; row < tokens_dd.size() - 1; row++) {
					sum += stol(tokens_dd[row][col]);
				}
				grandTotal += sum;
			}
			else if (op == "*") {
				u64 product = 1;
				for (int row = 0; row < tokens_dd.size() - 1; row++) {
					product *= stol(tokens_dd[row][col]);
				}
				grandTotal += product;
			}
			else {
				cout << "Error parsing input, unknown operation" << endl;
				assert(false);
			}
		}

		cout << grandTotal << endl;
	}

	void part2() {
		Initialize();

		u64 grandTotal = 0;
		vector <u32> columnNumbers;
		for (int col = input[0].size() - 1; col >= 0; col--) {
			u32 currentNumber = 0;
			for (int row = 0; row < input.size() - 1; row++) {
				char c = input[row][col];
				if (isDigit(c)) {
					currentNumber = 10 * currentNumber + (c - '0');
				}
			}
			if (currentNumber != 0) {
				columnNumbers.push_back(currentNumber);
				logger.info("Add number " + to_string(currentNumber));
			}

			auto op = input[input.size() - 1][col];
			if (op == '+') {
				u64 sum = 0;
				logger.info("Adding numbers: ");
				for (const auto& number: columnNumbers) {
					logger.info(to_string(number));
					sum += number;
				}
				grandTotal += sum;
				columnNumbers.clear();
			}
			else if (op == '*') {
				u64 product = 1;
				logger.info("Multiplying numbers: ");
				for (const auto& number : columnNumbers) {
					logger.info(to_string(number));
					product *= number;
				}
				grandTotal += product;
				columnNumbers.clear();
			}
		}

		cout << grandTotal << endl;
	}
}
