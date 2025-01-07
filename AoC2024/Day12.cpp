#include "day12.h"
#include "common.h"

#include <iostream>
#include <unordered_map>

using namespace std;

namespace
{
	struct GardenPlot
	{
		bool leftWall;
		bool rightWall;
		bool upperWall;
		bool lowerWall;
		char label;
		int plotId;

		GardenPlot()
		: leftWall { false }
		, rightWall{ false }
		, upperWall{ false }
		, lowerWall{ false }
		, label{ -1 }
		, plotId{ -1 }
		{}
	};

	struct RegionData {
		char regionLabel;
		int area;
		int perimeter;
		int sides;

		RegionData()
		: regionLabel{ -1 }
		, area{ -1 }
		, perimeter{-1}
		, sides{-1}
		{}
	};

	void expand_plot(int x, int y, int currentId, char label, vector<vector<GardenPlot>>& map)
	{
		// current plot already initialized
		if (map[y][x].plotId >= 0) {
			return;
		}

		if (map[y][x].label == label)
		{
			map[y][x].plotId = currentId;
			// check neighbors
			auto height = map.size();
			auto width = map[0].size();
			if (y > 0        ) { expand_plot(x    , y - 1, currentId, label, map); }
			if (y < height-1 ) { expand_plot(x    , y + 1, currentId, label, map); }
			if (x > 0        ) { expand_plot(x - 1,     y, currentId, label, map); }
			if (x < width - 1) { expand_plot(x + 1,     y, currentId, label, map); }
		}
	}

	
	void CalculatePlotIds(vector<vector<GardenPlot>>& plots_map) {
		int height = plots_map.size();
		int width = plots_map[0].size();

		int currentId = 0;
		for (auto y = 0; y < height; y++) {
			for (auto x = 0; x < width; x++) {
				if (plots_map[y][x].plotId < 0) {
					char label = plots_map[y][x].label;
					expand_plot(x, y, currentId, label, plots_map);
					currentId++;
				}
			}
		}
	}

	void PrintPlotIds(const vector<vector<GardenPlot>>& plots_map) {
		int height = plots_map.size();
		int width = plots_map[0].size();

		for (auto y = 0; y < height; y++) {
			for (auto x = 0; x < width; x++) {
				cout << plots_map[y][x].plotId;
			}
			cout << endl;
		}
	}

	void CalculateBorders(vector<vector<GardenPlot>>& map) {
		int height = map.size();
		int width = map[0].size();
		for (auto y = 0; y < height; y++) {
			for (auto x = 0; x < width; x++) {
				char this_label = map[y][x].label;
				// left border
				if (x == 0 || map[y][x - 1].label != this_label) {
					map[y][x].leftWall = true;
				}
				// right border
				if (x == (map[0].size() - 1) || map[y][x + 1].label != this_label) {
					map[y][x].rightWall = true;
				}
				// upper border
				if (y == 0 || map[y - 1][x].label != this_label) {
					map[y][x].upperWall = true;
				}
				// lower border
				if (y == (map.size() - 1) || map[y + 1][x].label != this_label) {
					map[y][x].lowerWall = true;
				}
			}
		}
	}

	void PrintBorders(const vector<vector<GardenPlot>>& map) {
		int height = map.size();
		int width = map[0].size();

		for (auto y = 0; y < height; y++) {
			// upper walls
			for (auto x = 0; x < width; x++) {
				cout << " ";
				cout << (map[y][x].upperWall ? "-" : ".");
				cout << " ";
			}
			cout << endl;
			// left, right
			for (auto x = 0; x < width; x++) {
				cout << (map[y][x].leftWall ? "|" : ".");
				cout << map[y][x].label;
				cout << (map[y][x].rightWall ? "|" : ".");
			}
			cout << endl;
			// lower walls
			for (auto x = 0; x < width; x++) {
				cout << " ";
				cout << (map[y][x].lowerWall ? "-" : ".");
				cout << " ";
			}
			cout << endl;
		}
	}

	int CalculateRegionArea(int regionId, const vector<vector<GardenPlot>>& map) {
		int area = 0;

		int height = map.size();
		int width = map[0].size();

		for (auto y = 0; y < height; y++) {
			for (auto x = 0; x < width; x++) {
				if (map[y][x].plotId == regionId) {
					area++;
				}
			}
		}
		return area;
	}

	int CalculateRegionPerimeter(int regionId, const vector<vector<GardenPlot>>& map) {
		int perimeter = 0;

		int height = map.size();
		int width = map[0].size();

		for (auto y = 0; y < height; y++) {
			for (auto x = 0; x < width; x++) {
				if (map[y][x].plotId == regionId) {
					if (map[y][x].lowerWall) { perimeter++; }
					if (map[y][x].upperWall) { perimeter++; }
					if (map[y][x].leftWall) { perimeter++; }
					if (map[y][x].rightWall) { perimeter++; }
				}
			}
		}
		return perimeter;
	}

	int CalculateRegionSides(int regionId, const vector<vector<GardenPlot>>& map) {
		int sides = 0;

		int height = map.size();
		int width = map[0].size();

		for (auto y = 0; y < height; y++) {
			for (auto x = 0; x < width; x++) {
				if (map[y][x].plotId == regionId) {
					// has lower wall
					if (map[y][x].lowerWall){
						// left neighbor has no lower wall
						if (x == 0 || map[y][x - 1].plotId != regionId || !map[y][x-1].lowerWall) sides++;
					}
					// has upper wall
					if (map[y][x].upperWall){
						// left neighbor has no upper wall
						if (x == 0 || map[y][x - 1].plotId != regionId || !map[y][x - 1].upperWall) sides++;
					}
					// has left wall
					if (map[y][x].leftWall){
						// upper neighbor has no left wall
						if (y == 0 || map[y-1][x].plotId != regionId || !map[y-1][x].leftWall) sides++;
					}
					// has right wall
					if (map[y][x].rightWall){
						// upper neighbor has no left wall
						if (y == 0 || map[y-1][x].plotId != regionId || !map[y - 1][x].rightWall) sides++;
					}
				}
			}
		}
		return sides;
	}
}

void
Day_12(const string& input_path)
{
	auto lines = get_input(input_path);

	int height = lines.size();
	int width = lines[0].size();

	vector<vector<GardenPlot>> plots_map;

	// Initialize data structure
	plots_map.resize(height);
	for (int y = 0; y < height; y++) {
		plots_map[y].resize(width);
		for (int x = 0; x < width; x++) {
			plots_map[y][x].label = lines[y][x];
		}
	}

	CalculatePlotIds(plots_map);
	//PrintPlotIds(plots_map);
	CalculateBorders(plots_map);
	//PrintBorders(plots_map);
	
	unordered_map<int, RegionData> regions;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			auto id = plots_map[y][x].plotId;
			if (regions.find(id) == regions.end()) {
				regions[id] = {};
				regions[id].area = CalculateRegionArea(id, plots_map);
				regions[id].perimeter = CalculateRegionPerimeter(id, plots_map);
				regions[id].sides = CalculateRegionSides(id, plots_map);
			}
		}
	}

	int total_price_perimter = 0;
	int total_price_sides = 0;
	for (auto& region : regions) {
		total_price_perimter += region.second.area * region.second.perimeter;
		total_price_sides += region.second.area * region.second.sides;
	}


	cout << total_price_perimter << endl;
	cout << total_price_sides << endl;
}
