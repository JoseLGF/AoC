#include "day03.h"

#include "common.h"

#include <iostream>
#include <regex>

using namespace std;

namespace {

	void part1(const string& input_path)
	{
		string test = get_input_string(input_path);

		// search for mul operations in input with regex
		regex mul_reg(R"(mul\((\d{1,3}),(\d{1,3})\))", regex_constants::ECMAScript);
		auto mul_begin = sregex_iterator(test.begin(), test.end(), mul_reg);
		auto mul_end = sregex_iterator();

		// iterate matches and calculate result
		int part1_result = 0;
		for (sregex_iterator i = mul_begin; i != mul_end; i++) {
			smatch match = *i;
			string match_str = match.str();
			//cout << match_str << " nums = " << match[1] << ", " << match[2] << '\n';
			part1_result += stoi(match[1]) * stoi(match[2]);
		}
		cout << part1_result << endl;
	}

	void part2(const string& input_path)
	{
		string test = get_input_string(input_path);

		// search for mul operations in input with regex
		regex mul_reg(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
		auto mul_begin = sregex_iterator(test.begin(), test.end(), mul_reg);
		auto mul_end = sregex_iterator();

		// iterate matches and calculate result
		int part2_result = 0;
		bool mul_enabled = true;
		for (sregex_iterator i = mul_begin; i != mul_end; i++) {
			smatch match = *i;
			string match_str = match.str();
			if (match_str == "do()") {
				mul_enabled = true;
			}
			else if (match_str == "don't()") {
				mul_enabled = false;
			}
			else if (mul_enabled) {
				//cout << match_str << " nums = " << match[1] << ", " << match[2] << '\n';
				part2_result += stoi(match[1]) * stoi(match[2]);
			}

		}
		cout << part2_result << endl;
	}
}

void
Day_03(const string& input_path)
{
	part1(input_path);
	part2(input_path);
	
}
