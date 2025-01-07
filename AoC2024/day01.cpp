#include "day01.h"

#include "common.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <unordered_map>

using namespace std;

namespace {
}

void
Day_01(const string& input_path)
{
	auto lines{ get_input(input_path) };

	vector<int> left_list{};
	vector<int> right_list{};

	for (auto& line : lines) {
		auto tokens{ tokenize_string(line) };
		left_list.push_back(stoi(tokens[0]));
		right_list.push_back(stoi(tokens[3]));
	}

	sort(left_list.begin(), left_list.end());
	sort(right_list.begin(), right_list.end());

	auto result_part1 = transform_reduce(
		left_list.begin(),
		left_list.end(),
		right_list.begin(),
		0,
		plus<>(),
		[](auto left, auto right) { return abs(left - right); }
	);

	cout << result_part1 << endl;

	unordered_map<int, int> occurences;
	for (auto& occ : right_list) {
		occurences[occ]++;
	}

	auto result_part2_other = transform_reduce(
		left_list.begin(),
		left_list.end(),
		0,
		plus<>(),
		[&](auto e) { return e * occurences[e]; }
	);

	cout << result_part2_other << endl;
}
