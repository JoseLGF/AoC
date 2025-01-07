#include "day10.h"
#include "common.h"

#include <iostream>

using namespace std;

namespace
{
	vector<pair<int, int>> find_trailheads(const vector<vector<int>>& map) {
		vector<pair<int, int>> trailheads;
		for (int y = 0; y < map.size(); y++) {
			for (int x = 0; x < map[0].size(); x++) {
				if (map[y][x] == 0) {
					trailheads.push_back(make_pair(x, y));
				}
			}
		}
		return trailheads;
	}

	void print_map(const vector<vector<int>>& map) {
		for (int y = 0; y < map.size(); y++) {
			for (int x = 0; x < map[0].size(); x++) {
				cout << map[y][x];
			}
			cout << endl;
		}
	}

	int xy_to_index(int x, int y, int width, int height) {
		return width * y + x;
	}

	int expand_trailhead_score(const pair<int, int>& current_location, const vector<vector<int>>& map, vector<bool>& expanded9s) {
		int score = 0;
		const auto x = current_location.first;
		const auto y = current_location.second;
		if (
			map[y][x] == 9 &&
			expanded9s[xy_to_index(x, y, map[0].size(), map.size())] == false
		) {
			expanded9s[xy_to_index(x, y, map[0].size(), map.size())] = true;
			return 1;
		}

		if (x > 0 && map[y][x - 1] == (map[y][x] + 1)) {
			score += expand_trailhead_score(make_pair(x - 1, y), map, expanded9s);
		}
		if (x < (map[0].size()-1) && map[y][x + 1] == (map[y][x] + 1)) {
			score += expand_trailhead_score(make_pair(x + 1, y), map, expanded9s);
		}
		if (y > 0 && map[y-1][x] == (map[y][x] + 1)) {
			score += expand_trailhead_score(make_pair(x, y-1), map, expanded9s);
		}
		if (y < (map.size()-1) && map[y+1][x] == (map[y][x] + 1)) {
			score += expand_trailhead_score(make_pair(x, y+1), map, expanded9s);
		}
		return score;
	}

	int calculate_trailhead_score(const pair<int,int>& trailhead, const vector<vector<int>>& map) {
		vector<bool> expanded_9s(map.size()*map[0].size(), false);
		return expand_trailhead_score(trailhead, map, expanded_9s);
	}

	int expand_trailhead_rating(const pair<int, int>& current_location, const vector<vector<int>>& map) {
		int score = 0;
		const auto x = current_location.first;
		const auto y = current_location.second;
		if (map[y][x] == 9) {
			return 1;
		}

		if (x > 0 && map[y][x - 1] == (map[y][x] + 1)) {
			score += expand_trailhead_rating(make_pair(x - 1, y), map);
		}
		if (x < (map[0].size() - 1) && map[y][x + 1] == (map[y][x] + 1)) {
			score += expand_trailhead_rating(make_pair(x + 1, y), map);
		}
		if (y > 0 && map[y - 1][x] == (map[y][x] + 1)) {
			score += expand_trailhead_rating(make_pair(x, y - 1), map);
		}
		if (y < (map.size() - 1) && map[y + 1][x] == (map[y][x] + 1)) {
			score += expand_trailhead_rating(make_pair(x, y + 1), map);
		}
		return score;
	}

	int calculate_trailhead_rating(const pair<int, int>& trailhead, const vector<vector<int>>& map) {
		return expand_trailhead_rating(trailhead, map);
	}
}

void
Day_10(const string& input_path)
{
	auto lines = get_input(input_path);
	auto height = lines.size();
	auto width = lines[0].size();
	vector<vector<int>> map;
	for (int y = 0; y < height; y++) {
		map.push_back({});
		for (int x = 0; x < width; x++) {
			map[y].push_back(lines[y][x] - '0');
		}
	}

	// show trailheads
	auto trailheads = find_trailheads(map);

	int sum_trailheads_scores = 0;
	for (auto& trailhead : trailheads) {
		auto score = calculate_trailhead_score(trailhead, map);
		sum_trailheads_scores += score;
	}
	cout << sum_trailheads_scores << endl;

	int sum_trailheads_ratings = 0;
	for (auto& trailhead : trailheads) {
		auto score = calculate_trailhead_rating(trailhead, map);
		sum_trailheads_ratings += score;
	}
	cout << sum_trailheads_ratings << endl;
}
