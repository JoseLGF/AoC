#include "common.h"

#include <iostream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include <cstdint>
#include <tuple>
#include <utility>
#include <set>

using namespace std;

namespace {
	const bool test_input = false;
	const int day = 8;
	vector<string> input;

	const int numConnections = test_input ? 10 : 1000;
	vector<tuple<int, int, int>> points;

	void Initialize() {
		static bool initialized = false;
		if (initialized) return;

		input = get_input(day, test_input);
		initialized = true;

		for (int i = 0; i < input.size(); i++) {
			int x;
			int y;
			int z;
			char c;

			auto line = input[i];
			stringstream ss(line);
			ss >> x >> c >> y >> c >> z;
			points.push_back({ x, y, z });
		}
	}
}

namespace aoc2025::day08 {
	typedef tuple<i64, i64, i64> Point3d;
	typedef tuple<int, int, u64> PointConnection;

	Point3d getPoint(int index) {
		assert(index < input.size());

		return points[index];
	}

	string strPoint(int index) {
		assert(index < input.size());

		auto [x, y, z] = getPoint(index);

		return "(" + to_string(x) + "," + to_string(y) + "," + to_string(z) + ")";
	}

	bool sortConnectionByDistance(const std::tuple<int, int, u64>& a, const std::tuple<int, int, u64>& b) {
		return std::get<2>(a) < std::get<2>(b);
	}

	void dfs(const vector<vector<int>>& adj, vector<bool>& visited, int s, vector<int>& res) {
		visited[s] = true;
		res.push_back(s);

		// Recursively visit all adjacent 
		// vertices that are not visited yet
		for (int i : adj[s]) {
			if (!visited[i]) {
				dfs(adj, visited, i, res);
			}
		}
	}

	vector<vector<int>> getConnectedComponents(const vector<vector<int>>& adj) {
		int V = adj.size();
		vector<bool> visited(V, false);
		vector<vector<int>> res;

		// Loop through all vertices 
		// to handle all components
		for (int i = 0; i < V; i++) {
			if (!visited[i]) {
				vector<int> component;
				dfs(adj, visited, i, component);
				res.push_back(component);
			}
		}

		return res;
	}

	u64 distance(i64 x1, i64 y1, i64 z1, i64 x2, i64 y2, i64 z2) {
		u64 result = 0;
		result += (x1 - x2) * (x1 - x2);
		result += (y1 - y2) * (y1 - y2);
		result += (z1 - z2) * (z1 - z2);
		return result;
	}

	void part1() {
		Initialize();

		int nJunctions = input.size();

		vector<PointConnection> connections;
		for (int i = 0; i < nJunctions; i++) {
			for (int j = i + 1; j < nJunctions; j++) {
				auto [x1, y1, z1] = getPoint(i);
				auto [x2, y2, z2] = getPoint(j);
				auto d = distance(x1, y1, z1, x2, y2, z2);
				connections.push_back({ i, j, d });
			}
		}

		sort(connections.begin(), connections.end(), sortConnectionByDistance);

		// Construct adjacency list
		vector<vector<int>> adjacencyList;
		for (int i = 0; i < nJunctions; i++) {
			adjacencyList.push_back({});
		}
		for (int c = 0; c < numConnections; c++) {
			auto [i, j, d] = connections[c];
			adjacencyList[i].push_back(j);
			adjacencyList[j].push_back(i);
		}

		auto components = getConnectedComponents(adjacencyList);
		sort(
			components.begin(),
			components.end(),
			[](const vector<int>& a, const vector<int>& b) { return a.size() > b.size(); }
		);

		u64 product = 1;
		product *= components[0].size();
		product *= components[1].size();
		product *= components[2].size();

		cout << product << endl;
	}

	void part2() {
		Initialize();
		int nJunctions = input.size();

		vector<PointConnection> connections;
		for (int i = 0; i < nJunctions; i++) {
			for (int j = i + 1; j < nJunctions; j++) {
				auto [x1, y1, z1] = getPoint(i);
				auto [x2, y2, z2] = getPoint(j);
				auto d = distance(x1, y1, z1, x2, y2, z2);
				connections.push_back({ i, j, d });
			}
		}

		sort(connections.begin(), connections.end(), sortConnectionByDistance);

		// Construct adjacency list
		vector<vector<int>> adjacencyList;
		for (int i = 0; i < nJunctions; i++) {
			adjacencyList.push_back({});
		}

		for (int c = 0; c < connections.size(); c++) {
			auto& [i, j, d] = connections[c];
			adjacencyList[i].push_back(j);
			adjacencyList[j].push_back(i);

			auto components = getConnectedComponents(adjacencyList);
			if (components.size() == 1) {
				auto [x1, y1, z1] = getPoint(i);
				auto [x2, y2, z2] = getPoint(j);
				cout << x1 * x2 << endl;
				break;
			}
		}
	}
}
