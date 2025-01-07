#include "day04.h"

#include "common.h"

#include <iostream>

using namespace std;

void
Day_04(const string& input_path)
{
	auto lines{ get_input(input_path) };

	auto width = lines[0].size();
	auto height = lines.size();

	int instances = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			// horizontal
			if (x + 3 < width) {
				// forward
				if (lines[y][x] == 'X' && lines[y][x + 1] == 'M' && lines[y][x + 2] == 'A' && lines[y][x + 3] == 'S') instances++;
				// backward
				if (lines[y][x] == 'S' && lines[y][x + 1] == 'A' && lines[y][x + 2] == 'M' && lines[y][x + 3] == 'X') instances++;
			}
			// vertical
			if (y + 3 < height) {
				// forward
				if (lines[y][x] == 'X' && lines[y + 1][x] == 'M' && lines[y + 2][x] == 'A' && lines[y + 3][x] == 'S') instances++;
				// backward
				if (lines[y][x] == 'S' && lines[y + 1][x] == 'A' && lines[y + 2][x] == 'M' && lines[y + 3][x] == 'X') instances++;
			}
			// diagonal decreasing
			if ((x + 3 < width) && (y + 3 < height)) {
				// forward
				if (lines[y][x] == 'X' && lines[y + 1][x + 1] == 'M' && lines[y + 2][x + 2] == 'A' && lines[y + 3][x + 3] == 'S') instances++;
				// backward
				if (lines[y][x] == 'S' && lines[y + 1][x + 1] == 'A' && lines[y + 2][x + 2] == 'M' && lines[y + 3][x + 3] == 'X') instances++;
			}
			// diagonal increasing
			if ((x + 3 < width) && (y - 3 < height)) {
				// forward
				if (lines[y][x] == 'X' && lines[y - 1][x + 1] == 'M' && lines[y - 2][x + 2] == 'A' && lines[y - 3][x + 3] == 'S') instances++;
				// backward
				if (lines[y][x] == 'S' && lines[y - 1][x + 1] == 'A' && lines[y - 2][x + 2] == 'M' && lines[y - 3][x + 3] == 'X') instances++;
			}
		}
	}

	cout << instances << endl;

	int mas_instances = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if ((x + 2 < width) && (y + 2 < height)) {
				if (
					(lines[y][x] == 'M' && lines[y + 1][x + 1] == 'A' && lines[y + 2][x + 2] == 'S') ||
					(lines[y][x] == 'S' && lines[y + 1][x + 1] == 'A' && lines[y + 2][x + 2] == 'M')
					)
				{
					if (
						(lines[y + 2][x] == 'M' && lines[y + 1][x + 1] == 'A' && lines[y][x + 2] == 'S') ||
						(lines[y + 2][x] == 'S' && lines[y + 1][x + 1] == 'A' && lines[y][x + 2] == 'M')
						) {
						mas_instances++;
					}
				}
			}
		}
	}

	cout << mas_instances << endl;
}