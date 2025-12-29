#include "common.h"
#include "logger.h"

#include <iostream>
#include <tuple>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <set>

using namespace std;

namespace {
	Logger logger("Day9", true);
	const bool test_input = false;
	const int day = 9;
	vector<string> input;

	vector<tuple<int, int>> redTiles;
	set<tuple<u64, u64>> edges;
	enum class Direction {
		Up, Down, Left, Right
	};

	void Initialize() {
		static bool initialized = false;
		if (initialized) return;

		input = get_input(day, test_input);
		initialized = true;

		for (auto line : input) {
			stringstream s(line);
			int x;
			int y;
			char c;
			s >> x >> c >> y;
			redTiles.push_back({ x, y });
		}
	}

	auto getArea = [](const tuple<i64, i64>& p1, const tuple<i64, i64>& p2) -> u64 {
		const auto& [x1, y1] = p1;
		const auto& [x2, y2] = p2;
		return abs((x1 - x2 + 1) * (y1 - y2 + 1));
	};

	bool doesSegmentCutArea(
		const tuple<i64, i64>& segmentp1,
		const tuple<i64, i64>& segmentp2,
		const tuple<i64, i64>& areap1,
		const tuple<i64, i64>& areap2)
	{
		const auto [sp1x, sp1y] = segmentp1;
		const auto [sp2x, sp2y] = segmentp2;
		const auto [ap1x, ap1y] = areap1;
		const auto [ap2x, ap2y] = areap2;

		const auto aleft = min(ap1x, ap2x);
		const auto aright = max(ap1x, ap2x);
		const auto aceil = min(ap1y, ap2y);
		const auto afloor = max(ap1y, ap2y);

		const auto sleft = min(sp1x, sp2x);
		const auto sright = max(sp1x, sp2x);
		const auto sceil = min(sp1y, sp2y);
		const auto sfloor = max(sp1y, sp2y);

		// horizontal segment
		if (sp1y == sp2y) {
			if (sceil <= aceil || sfloor >= afloor) {
				return false;
			}
			if (sleft >= aright || sright <= aleft) {
				return false;
			}
			return true;
		}
		// vertical segment
		else if (sp1x == sp2x) {
			if (sleft <= aleft || sright >= aright) {
				return false;
			}
			if (sceil >= afloor || sfloor <= aceil) {
				return false;
			}
			return true;
		}
		else {
			assert(false);
		}
	}

	bool isValidArea(const tuple<i64, i64>& ap1, const tuple<i64, i64>& ap2) {
		/*
		for (const auto& redTile : redTiles) {
			if (redTile == p1 || redTile == p2) {
				continue;
			}
			const auto& [rtx, rty] = redTile;
			if ( (rtx > left) || (rtx < right) || (rty > ceil) || (rty < floor) ) {
				return false;
			}
		}
		*/
		const auto [ap1x, ap1y] = ap1;
		const auto [ap2x, ap2y] = ap2;

		const auto aleft = min(ap1x, ap2x);
		const auto aright = max(ap1x, ap2x);
		const auto aceil = min(ap1y, ap2y);
		const auto afloor = max(ap1y, ap2y);

		for (int x = aleft; x < aright; x++) {
			if (edges.find({ x, aceil }) != edges.end()) {
				return false;
			}
		}
		for (int x = aleft; x < aright; x++) {
			if (edges.find({ x, afloor }) != edges.end()) {
				return false;
			}
		}
		for (int y = aceil; y < afloor; y++) {
			if (edges.find({ aleft, y }) != edges.end()) {
				return false;
			}
		}
		for (int y = aceil; y < afloor; y++) {
			if (edges.find({ aleft, y }) != edges.end()) {
				return false;
			}
		}

		/*for (int i = 0; i < redTiles.size() - 1; i++) {
			const auto& s1 =redTiles[i];
			const auto& s2 = redTiles[i+1];
			if (doesSegmentCutArea(s1, s2, ap1, ap2)) {
				return false;
			}
		}
		*/
		return true;
	}
}

namespace aoc2025::day09 {
	void part1() {
		Initialize();

		u64 maxArea = 0;
		for (int i = 0; i < redTiles.size(); i++) {
			for (int j = i + 1; j < redTiles.size(); j++) {
				u64 area = getArea(redTiles[i], redTiles[j]);
				if (area > maxArea) {
					maxArea = area;
				}
			}
		}
		cout << maxArea << endl;
	}

	void part2() {
		Initialize();

		// build outer edge
		logger.info("Building map of outer edge tiles. . .");
		Direction initialDirection = Direction::Right;
		for (int i = 0; i < redTiles.size()-1; i++) {
			const auto [sp1x, sp1y] = redTiles[i];
			const auto [sp2x, sp2y] = redTiles[i+1];

			const auto sleft = min(sp1x, sp2x);
			const auto sright = max(sp1x, sp2x);
			const auto sceil = min(sp1y, sp2y);
			const auto sfloor = max(sp1y, sp2y);
			// horizontal segment
			if (sp1y == sp2y) {
				// segment goes left
				if (sp1x > sp1y) {
					for (int x = sleft; x < sright; x++) {
						edges.insert({ x, sceil - 1 });
					}
				}
				// segment goes right
				else {
					for (int x = sleft; x < sright; x++) {
						edges.insert({ x, sceil + 1 });
					}
				}
			}
			// vertical segment
			else if (sp1x == sp2x) {
				// segment goes up
				if (sp1y > sp2y) {
					for (int y = sceil; y < sfloor; y++) {
						edges.insert({ sleft + 1, y });
					}
				}
				// segment goes down
				else {
					for (int y = sceil; y < sfloor; y++) {
						edges.insert({ sleft - 1, y });
					}
				}
			}
			else {
				assert(false);
			}
		}

		u64 maxArea = 0;
		u64 areaCounter = 0;
		u64 allAreasCount = redTiles.size() * redTiles.size() / 2;
		for (int i = 0; i < redTiles.size(); i++) {
			for (int j = i + 1; j < redTiles.size(); j++) {
				areaCounter++;
				logger.info("Checking valid area " + to_string(areaCounter) + " of " + to_string(allAreasCount));
				if (isValidArea(redTiles[i], redTiles[j])) {
					u64 area = getArea(redTiles[i], redTiles[j]);
					if (area > maxArea) {
						maxArea = area;
					}
				}
			}
		}
		cout << maxArea << endl;
	}
}
