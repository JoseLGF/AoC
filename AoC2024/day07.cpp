#include "day07.h"
#include "common.h"

#include <iostream>
#include <sstream>
#include <numeric>

using namespace std;

namespace
{
	struct Equation {
		long long int test_value;
		vector<long long int> numbers;
	};

	Equation parse_equation(const string& str) {
		Equation out;
		stringstream ss(str);
		long long int i;
		char c;

		ss >> i;
		out.test_value = i;
		ss >> c; // colon
		while (!ss.eof()) {
			ss >> i;
			out.numbers.push_back(i);
		}
		
		return out;
	}

	bool expand_equation_2ops(const Equation& eq, int current_index, long long int current_value)
	{
		if (current_value == eq.test_value) return true;

		if (current_value > eq.test_value) return false;
		if (current_index >= eq.numbers.size()) return false;

		if (expand_equation_2ops(eq, current_index + 1, current_value + eq.numbers[current_index])) return true;
		if (current_value != 0) {
			return expand_equation_2ops(eq, current_index + 1, current_value * eq.numbers[current_index]);
		}
	}

	bool expand_equation_3ops(const Equation& eq, int current_index, long long int current_value)
	{
		if (current_index == eq.numbers.size() && current_value == eq.test_value) {
			return true;
		}

		if (current_value > eq.test_value) return false;
		if (current_index >= eq.numbers.size()) return false;

		if (expand_equation_3ops(eq, current_index + 1, current_value + eq.numbers[current_index])) return true;
		if (current_value != 0) {
			if (expand_equation_3ops(eq, current_index + 1, current_value * eq.numbers[current_index])) return true;

			string s = to_string(current_value) + to_string(eq.numbers[current_index]);
			long long int concat = stoll(s);
			return expand_equation_3ops(eq, current_index + 1, concat);
		}
		return false;
	}

	bool is_equation_valid_2ops(const Equation& eq)
	{
		return expand_equation_2ops(eq, 0, 0);
	}

	bool is_equation_valid_3ops(const Equation& eq)
	{
		return expand_equation_3ops(eq, 1, eq.numbers[0]);
	}
}

void
Day_07(const string& input_path)
{
	auto lines = get_input(input_path);
	vector<Equation> equations;

	for (auto& line : lines) {
		equations.push_back(parse_equation(line));
	}

	long long int total_calibration_result_part1 = 0;
	for (int i = 0; i < equations.size(); i++ ) {
		auto eq = equations[i];
		if (is_equation_valid_2ops(eq)) {
			total_calibration_result_part1 += eq.test_value;
		}
	}
	cout << total_calibration_result_part1 << endl;

	long long int total_calibration_result_part2 = 0;
	for (int i = 0; i < equations.size(); i++) {
		auto& eq = equations[i];
		if (is_equation_valid_3ops(eq)) {
			total_calibration_result_part2 += eq.test_value;
		}
	}
	cout << total_calibration_result_part2 << endl;
}
