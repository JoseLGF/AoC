#include "day02.h"

#include "common.h"

#include <algorithm>
#include <iostream>

using namespace std;

namespace {
}

void
Day_02(const string& input_path)
{
	auto lines{ get_input(input_path) };

	vector<vector<int>> reports;

	for (auto& line : lines) {
		auto tokens{ tokenize_string(line) };
		reports.push_back({});

		for (auto& token : tokens) {
			reports.back().push_back(stoi(token));
		}
	}

	auto monotonically_increasing = [](const vector<int>& levels)
		{
			auto min{ numeric_limits<int>::min() };
			for (auto& level : levels) {
				if (level <= min) {
					return false;
				}
				min = level;
			}
			return true;
		};

	auto monotonically_decreasing = [](const vector<int>& levels)
		{
			auto max{ numeric_limits<int>::max() };

			for (auto& level : levels) {
				if (level >= max) {
					return false;
				}
				max = level;
			}
			return true;
		};

	auto check_deltas = [](const vector<int>& levels)
		{
			for (int i = 1; i < levels.size(); i++) {
				auto delta = abs(levels[i] - levels[i - 1]);
				if (delta < 1 || delta > 3) {
					return false;
				}
			}
			return true;
		};

	auto is_report_safe = [&](vector<int> levels) {
		return
			(monotonically_increasing(levels) || monotonically_decreasing(levels)) &&
			check_deltas(levels);
		};

	auto safe_reports{ count_if(reports.begin(), reports.end(), is_report_safe) };
	cout << safe_reports << endl;

	int safe_reports_damped = 0;
	for (auto& report : reports) {
		if (is_report_safe(report)) {
			safe_reports_damped++;
			continue;
		}
		// Apply damping by removing each element
		for (int i = 0; i < report.size(); i++) {
			auto report_copy = report;
			report_copy.erase(report_copy.begin() + i);
			if (is_report_safe(report_copy)) {
				safe_reports_damped++;
				break;
			}
		}
	}

	cout << safe_reports_damped << endl;
}
