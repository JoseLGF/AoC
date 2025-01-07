#include "day05.h"
#include "common.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace
{
	bool
	check_update(const vector<int>& update, const vector<pair<int, int>>& rules)
	{
		for (auto& rule : rules) {
			auto first = rule.first;
			auto second = rule.second;
			auto first_it = find(update.begin(), update.end(), first);
			auto second_it = find(update.begin(), update.end(), second);

			// ignore rule if it does not apply
			if (first_it == update.end() || second_it == update.end()) continue;

			if (second_it <= first_it) {
				return false;
			}
		}
		return true;
	}

	vector<int>
	fix_update(const vector<int>& update, const vector<pair<int, int>>& rules)
	{
		vector<int> fixed_update;

		for (auto& element : update) {
			for (int i = 0; i <= fixed_update.size(); i++) {
				auto test_update = fixed_update;
				auto it = test_update.insert(test_update.begin() + i, element);
				if (check_update(test_update, rules)) {
					fixed_update = test_update;
					break;
				}
			}
		}

		return fixed_update;
	}
}


void
Day_05(const string& input_path)
{
	auto lines{ get_input(input_path) };

	vector<pair<int, int>> rules;
	int line_index = 0;
	// read rules
	do {
		auto line = lines[line_index];
		string left = line.substr(0, 2);
		string right = line.substr(3, 2);
		rules.push_back(make_pair(stoi(left), stoi(right)));
		line_index++;
	} while (lines[line_index].size() != 0);
	line_index++;
	// read updates
	vector<vector<int>> updates;
	while (line_index < lines.size()) {
		auto update = read_comma_separated_ints_line(lines[line_index]);
		updates.push_back(update);
		line_index++;
	}

	// Check updates ordering
	vector<vector<int>> incorrect_updates;
	int part1_result = 0;
	cout << "Correct updates:" << endl;
	for (auto& update : updates) {
		if (check_update(update, rules)) {
			part1_result += update[update.size() / 2];
		}
		else {
			incorrect_updates.push_back(update);
		}
	}
	cout << part1_result << endl;

	vector<vector<int>> fixed_updates;
	for (auto& incorrect_update : incorrect_updates) {
		fixed_updates.push_back(fix_update(incorrect_update, rules));
	}

	int part2_result = 0;
	for (auto& fixed_update : fixed_updates) {
		part2_result += fixed_update[fixed_update.size() / 2];
	}

	cout << part2_result << endl;
}
