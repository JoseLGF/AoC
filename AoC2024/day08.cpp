#include "day08.h"
#include "common.h"

#include <iostream>

using namespace std;

namespace
{
	const string freqs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	void Part1(const string& input_path) {
		auto map = get_input(input_path);
		int height = map.size();
		int width = map[0].size();

		auto isPosValid = [&](int x, int y) {
			return x >= 0 && x < width && y >= 0 && y < height;
			};
		
		vector<vector<bool>> antinodes;
		for (int i = 0; i < height; i++) {
			antinodes.push_back({});
			for (int j = 0; j < width; j++) {
				antinodes[i].push_back(false);
			}
		}

		for (int i = 0; i < freqs.size(); i++) {
			char c = freqs[i];
			vector<pair<int, int>> freq_positions;
			// find all antennas with current frequency
			//cout << "Searching antennas of freq " << c << endl;
			for (int x = 0; x < map.size(); x++) {
				for (int y = 0; y < map[0].size(); y++) {
					char e = map[y][x];
					if (e == c) {
						//cout << e << ":" << x << "," << y << endl;
						freq_positions.push_back(make_pair(x, y));
					}
				}
			}
			// calculate all antinodes
			//cout << "Calculating antinodes for " << freq_positions.size() << " antennas" << endl;
			if (freq_positions.size() < 2) continue;
			for (int ai = 0; ai < freq_positions.size() - 1; ai++) {
				for (int bi = ai + 1; bi < freq_positions.size(); bi++) {
					int x_1 = freq_positions[ai].first;
					int x_2 = freq_positions[bi].first;
					int y_1 = freq_positions[ai].second;
					int y_2 = freq_positions[bi].second;
					int x_offset = x_2 - x_1;
					int y_offset = y_2 - y_1;
					// calculate antinodes
					int a1_x = x_1 - x_offset;
					int a2_x = x_2 + x_offset;
					int a1_y = y_1 - y_offset;
					int a2_y = y_2 + y_offset;
					// add valid antinodes
					if (isPosValid(a1_x, a1_y)) {
						antinodes[a1_y][a1_x] = true;
					}
					if (isPosValid(a2_x, a2_y)) {
						antinodes[a2_y][a2_x] = true;
					}
				}
			}
		}

		int unique_antinode_locations = 0;
		for (auto& row : antinodes) {
			for (auto pos : row) {
				if (pos) unique_antinode_locations++;
			}
		}
		cout << unique_antinode_locations << endl;
	}

	void Part2(const string& input_path) {
		auto map = get_input(input_path);
		int height = map.size();
		int width = map[0].size();

		auto isPosValid = [&](int x, int y) {
			return x >= 0 && x < width && y >= 0 && y < height;
			};

		vector<vector<bool>> antinodes;
		for (int i = 0; i < height; i++) {
			antinodes.push_back({});
			for (int j = 0; j < width; j++) {
				antinodes[i].push_back(false);
			}
		}

		for (int i = 0; i < freqs.size(); i++) {
			char c = freqs[i];
			vector<pair<int, int>> freq_positions;
			// find all antennas with current frequency
			//cout << "Searching antennas of freq " << c << endl;
			for (int x = 0; x < map.size(); x++) {
				for (int y = 0; y < map[0].size(); y++) {
					char e = map[y][x];
					if (e == c) {
						//cout << e << ":" << x << "," << y << endl;
						freq_positions.push_back(make_pair(x, y));
					}
				}
			}
			// calculate all antinodes
			//cout << "Calculating antinodes for " << freq_positions.size() << " antennas" << endl;
			if (freq_positions.size() < 2) continue;
			for (int ai = 0; ai < freq_positions.size() - 1; ai++) {
				for (int bi = ai + 1; bi < freq_positions.size(); bi++) {
					
					int x_1 = freq_positions[ai].first;
					int x_2 = freq_positions[bi].first;
					int y_1 = freq_positions[ai].second;
					int y_2 = freq_positions[bi].second;
					int x_offset = x_2 - x_1;
					int y_offset = y_2 - y_1;
					// calculate antinodes
					bool continue_left = true;
					int antinode_i = 0;
					while (continue_left) {
						int a1_x = x_1 - x_offset * antinode_i;
						int a1_y = y_1 - y_offset * antinode_i;
						if (isPosValid(a1_x, a1_y)) {
							antinodes[a1_y][a1_x] = true;
							antinode_i++;
						}
						else {
							continue_left = false;
						}
					}

					bool continue_right = true;
					antinode_i = 0;
					while (continue_right) {
						int a2_x = x_2 + x_offset * antinode_i;
						int a2_y = y_2 + y_offset * antinode_i;
						if (isPosValid(a2_x, a2_y)) {
							antinodes[a2_y][a2_x] = true;
							antinode_i++;
						}
						else {
							continue_right = false;
						}
					}
				}
			}
		}

		int unique_antinode_locations = 0;
		for (auto& row : antinodes) {
			for (auto pos : row) {
				if (pos) unique_antinode_locations++;
			}
		}
		cout << unique_antinode_locations << endl;
	}
}

void
Day_08(const string& input_path)
{
	Part1(input_path);
	Part2(input_path);
}
