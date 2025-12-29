#include "common.h"
#include "logger.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

namespace {
	Logger logger("Day2");
	vector<string> input;
}

namespace aoc2025::day02 {
	void part1() {
		input = get_input(2, false);
		assert(input.size() > 0);
		const auto& line = input[0];

		auto ranges = split_line(line);
		long long int invalidIdsSum = 0;

		for (const auto& range : ranges) {
			const auto ids = split_line(range, '-');
			const auto firstId = ids[0];
			const auto lastId = ids[1];

			logger.info("first: " + firstId + ", last: " + lastId);

			auto isValidId = [](long long int id) {
				const auto idStr = to_string(id);
				const auto strLen = idStr.length();
				if ((strLen % 2) != 0) {
					return true;
				}
				for (int i = 0; i < (strLen / 2); i++) {
					if (idStr[i] != idStr[i + strLen / 2]) {
						return true;
					}
				}
				return false;
			};

			for (long long int id = stoll(firstId); id <= stoll(lastId); id++) {
				if (!isValidId(id)) {
					logger.info("Invalid id: " + to_string(id));
					long long int newInvalidIdsSum = invalidIdsSum + id;
					if (newInvalidIdsSum < invalidIdsSum) {
						cout << "ERROR: Overflow detected!" << endl;
					}
					invalidIdsSum += id;
				}
			}
		}
		cout << invalidIdsSum << endl;
	}

	void part2() {
		const auto& line = input[0];

		auto ranges = split_line(line);
		long long int invalidIdsSum = 0;

		for (const auto& range : ranges) {
			const auto ids = split_line(range, '-');
			const auto firstId = ids[0];
			const auto lastId = ids[1];

			logger.info("first: " + firstId + ", last: " + lastId);

			auto isValidId = [](long long int id) {
				const auto idStr = to_string(id);
				const auto strLen = idStr.length();
				if ((strLen % 2) != 0) {
					return true;
				}
				for (int i = 0; i < (strLen / 2); i++) {
					if (idStr[i] != idStr[i + strLen / 2]) {
						return true;
					}
				}
				return false;
			};

			for (long long int id = stoll(firstId); id <= stoll(lastId); id++) {
				if (!isValidId(id)) {
					logger.info("Invalid id: " + to_string(id));
					long long int newInvalidIdsSum = invalidIdsSum + id;
					if (newInvalidIdsSum < invalidIdsSum) {
						cout << "Error: Overflow detected!" << endl;
					}
					invalidIdsSum += id;
				}
			}
		}
		cout << invalidIdsSum << endl;
	}
}