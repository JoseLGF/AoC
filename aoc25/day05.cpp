#include "common.h"
#include "logger.h"

#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <cstdint>

using namespace std;

namespace {
	Logger logger("Day5");
	vector<string> input;
}

namespace aoc2025::day05 {
	struct Range {
		uint64_t left;
		uint64_t right;
	};

	vector<Range> ranges;

	bool isIdInRange(const uint64_t id, const Range& range) {
		return id >= range.left && id <= range.right;
	};

	bool isIdFresh(const uint64_t id) {
		for (const auto& range : ranges) {
			if (isIdInRange(id, range)) {
				return true;
			}
		}
		return false;
	}

	vector<pair<uint64_t, uint64_t>> mergeRanges(const vector<Range>& r_ranges) {
		vector<pair<uint64_t, uint64_t> > ranges;
		for (const auto& range : r_ranges) {
			ranges.push_back(make_pair(range.left, range.right));
		}
		vector<pair<uint64_t, uint64_t> > result;
		sort(ranges.begin(), ranges.end());
		vector<pair<uint64_t, uint64_t> >::iterator it = ranges.begin();
		pair<uint64_t, uint64_t> current = *(it)++;
		while (it != ranges.end()) {
			if (current.second >= it->first) {
				current.second = max(current.second, it->second);
			}
			else {
				result.push_back(current);
				logger.info("add merged range: " + to_string(current.first) + "-" + to_string(current.second));
				current = *(it);
			}
			it++;
		}
		result.push_back(current);
		logger.info("add merged range: " + to_string(current.first) + "-" + to_string(current.second));

		return result;
	}

	void part1() {
		input = get_input(5, false);

		vector<string> freshRanges;
		vector<string> ingredientIds;
		bool parsingRanges = true;

		for (auto line : input) {
			if (parsingRanges) {
				if (line.empty()) {
					parsingRanges = false;
				}
				else {
					freshRanges.push_back(line);
				}
			}
			else {
				ingredientIds.push_back(line);
			}
		}

		for (const auto& range : freshRanges) {
			stringstream ss(range);
			char dash;
			uint64_t left;
			uint64_t right;
			ss >> left >> dash >> right;

			logger.info("Range: " + to_string(left) + "-" + to_string(right));
			ranges.push_back(Range{ .left = left, .right = right });
		}

		int freshIngredients = 0;
		for (const auto& id : ingredientIds) {
			stringstream ss(id);
			uint64_t idNr;
			ss >> idNr;

			if (isIdFresh(idNr)) {
				freshIngredients++;
			}
		}

		cout << freshIngredients << endl;
	}

	void part2() {
		auto mergedRanges = mergeRanges(ranges);

		uint64_t numberOfFreshIngredients = 0;
		for (const auto& range : mergedRanges) {
			numberOfFreshIngredients += (range.second - range.first + 1);
		}

		cout << numberOfFreshIngredients << endl;
	}
}
