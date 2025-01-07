#include "day11.h"
#include "common.h"

#include <iostream>
#include <unordered_map>

using namespace std;

namespace
{
	vector<long long int> blink(const vector<long long int>& stones) {
		vector<long long int> new_stones;
		for (auto& stone : stones) {
			// rule 1
			if (stone == 0) {
				new_stones.push_back(1);
			}
			else if ((to_string(stone).size() % 2) == 0) {
				auto str = to_string(stone);
				auto left = str.substr(0, str.length() / 2);
				auto right = str.substr(str.length() / 2, str.length() / 2);
				new_stones.push_back(stoll(left));
				new_stones.push_back(stoll(right));
			}
			else {
				new_stones.push_back(stone * 2024LL);
			}
		}
		return new_stones;
	}

	void print_stones(const vector<long long int>& stones) {
		for (auto stone : stones) {
			cout << stone << " ";
		}
		cout << endl;
	}

	long long int expand_stone(long long stone, int blinks, vector<unordered_map<long long int, long long int>>& memo) {
		if (blinks == 0) return 1;
		long long int stones = 0;

		// check if this stone has already been calculated for the given number of blinks
		auto& map = memo[blinks];
		if (map.find(stone) != map.end()) {
			return map[stone];
		}

		if (stone == 0) {
			stones += expand_stone(1, blinks -1, memo);
		}
		else if ((to_string(stone).size() % 2) == 0) {
			auto str = to_string(stone);
			auto left = str.substr(0, str.length() / 2);
			auto right = str.substr(str.length() / 2, str.length() / 2);
			stones += expand_stone(stoll(left), blinks -1, memo);
			stones += expand_stone(stoll(right), blinks - 1, memo);
		}
		else {
			stones += expand_stone(stone * 2024LL, blinks - 1, memo);
		}

		// insert newly calculated stone value
		map[stone] = stones;
		return stones;
	}
}

void
Day_11(const string& input_path)
{
	auto line = get_input_string(input_path);
	auto stones_str = tokenize_string(line);
	vector<long long int> stones;
	for (auto& stone_str : stones_str) {
		stones.push_back(stoll(stone_str));
	}

	const auto num_blinks = 25;
	long num_stones_after_25_blinks{};
	vector<long long int> new_stones = stones;
	for (auto i = 0; i < num_blinks; i++) {
		new_stones = blink(new_stones);
	}
	num_stones_after_25_blinks = new_stones.size();
	cout << num_stones_after_25_blinks << endl;


	long long int num_stones_after_75_blinks = 0;
	//                          stone -> num of stones
	vector<unordered_map<long long int, long long int>> memo(75+1);
	for (auto& stone : stones) {
		num_stones_after_75_blinks += expand_stone(stone, 75, memo);
	}
	cout << num_stones_after_75_blinks << endl;
}
