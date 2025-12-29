#include "common.h"
#include "logger.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

namespace {
	Logger logger("Day3");
	vector<string> input;
}

namespace aoc2025::day03 {
	void part1() {
		input = get_input(3, false);
		assert(input.size() > 0);

		int sumOfMaxJoltagesInAllBanks = 0;
		for (const auto& bank : input) {
			auto findLargestJoltageInBank = [](const string& bank) {
				int maxJoltage = 0;
				for (int i = 0; i < bank.size() - 1; i++) {
					int left = bank[i] - '0';
					for (int j = i + 1; j < bank.size(); j++) {
						int right = bank[j] - '0';
						int joltage = 10 * left + right;
						if (joltage > maxJoltage) {
							maxJoltage = joltage;
						}
					}
				}
				logger.info("maxJoltage for " + bank + ": " + to_string(maxJoltage));
				return maxJoltage;
			};
			sumOfMaxJoltagesInAllBanks += findLargestJoltageInBank(bank);
		}

		cout << sumOfMaxJoltagesInAllBanks << endl;
	}

	void part2() {
		long long int sumOfMaxJoltagesInAllBanks = 0;
		for (const auto& bank : input) {
			assert(bank.size() >= 12);
			vector<size_t> indeces;

			for (int i = 0; i < 12; i++) {
				indeces.push_back(bank.size() - 12 + i);
			}
			
			// traverse indeces, from left to right
			for (int i = 0; i < 12; i++) {
				int leftLimit = (i > 0) ? indeces[i - 1] : -1;
				int start = indeces[i];
				long long int maxJoltage = 0;
				int maxIndex = start;
				for (int j = start; j > leftLimit; j--) {
					int currentJoltage = bank[j];
					if (currentJoltage >= maxJoltage) {
						maxJoltage = currentJoltage;
						maxIndex = j;
					}
				}
				
				indeces[i] = maxIndex;
				logger.info("Select index " + to_string(i) + ": " + bank[maxIndex]);
			}

			// reconstruct the joltage from the indeces
			long long int bankMaxJoltage = 0;
			for (auto it = indeces.begin(); it != indeces.end(); ++it) {
				bankMaxJoltage = 10 * bankMaxJoltage + (bank[*it] - '0');
			}
			logger.info("max joltage for bank " + bank + ": " + to_string(bankMaxJoltage));

			sumOfMaxJoltagesInAllBanks += bankMaxJoltage;
		}

		cout << sumOfMaxJoltagesInAllBanks << endl;
	}
}
