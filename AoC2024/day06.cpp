#include "day06.h"

#include "common.h"

#include <iostream>

using namespace std;

namespace {

	int width;
	int height;

	const unsigned int kBitmaskUp    = 0b0001;
	const unsigned int kBitmaskDown  = 0b0010;
	const unsigned int kBitmaskLeft  = 0b0100;
	const unsigned int kBitmaskRight = 0b1000;

	int xyToId(int x, int y) {
		return y * width + x;
	}

	enum class Direction {
		Left, Right, Up, Down
	};

	enum class MapSquare {
		Free, Obstruction
	};

	enum class StepResult {
		Ok, OutOfBounds, LoopFound
	};

	struct State {
		int guard_position_x;
		int guard_position_y;
		Direction guard_direction;
		vector<MapSquare> map;
		vector<bool> visitedPositions;
		vector<unsigned int> visitedPosDirections;
	};

	void SetDirectionBit(unsigned int& n, Direction dir)
	{
		switch (dir) {
		case Direction::Up:
			n |= kBitmaskUp;
			break;
		case Direction::Down:
			n |= kBitmaskDown;
			break;
		case Direction::Left:
			n |= kBitmaskLeft;
			break;
		case Direction::Right:
			n |= kBitmaskRight;
			break;
		}
	}

	bool IsBitSet(unsigned int n, Direction dir) {
		switch (dir) {
		case Direction::Up:
			return (n & kBitmaskUp) != 0;
		case Direction::Down:
			return (n & kBitmaskDown) != 0;
		case Direction::Left:
			return (n & kBitmaskLeft) != 0;
		case Direction::Right:
			return (n & kBitmaskRight) != 0;
		}
	}

	StepResult AdvanceState(State& state) {
		int new_pos_x;
		int new_pos_y;
		// Determine heading position
		switch (state.guard_direction) {
			case Direction::Up:
				new_pos_x = state.guard_position_x;
				new_pos_y = state.guard_position_y - 1;
				break;
			case Direction::Down:
				new_pos_x = state.guard_position_x;
				new_pos_y = state.guard_position_y + 1;
				break;
			case Direction::Right:
				new_pos_x = state.guard_position_x + 1;
				new_pos_y = state.guard_position_y;
				break;
			case Direction::Left:
				new_pos_x = state.guard_position_x - 1;
				new_pos_y = state.guard_position_y;
				break;
			default:
				break;
		}
		// Check out of bounds
		if (new_pos_x < 0 || new_pos_x >= width || new_pos_y < 0 || new_pos_y >= height) {
			return StepResult::OutOfBounds;
		}
		// Check if new position is obstructed
		if (state.map[xyToId(new_pos_x, new_pos_y)] == MapSquare::Obstruction) {
			// Rotate 90 degrees
			switch (state.guard_direction) {
				case Direction::Up:
					state.guard_direction = Direction::Right;
					SetDirectionBit(state.visitedPosDirections[xyToId(state.guard_position_x, state.guard_position_y)], Direction::Right);
					break;
				case Direction::Right:
					state.guard_direction = Direction::Down;
					SetDirectionBit(state.visitedPosDirections[xyToId(state.guard_position_x, state.guard_position_y)], Direction::Down);
					break;
				case Direction::Down:
					state.guard_direction = Direction::Left;
					SetDirectionBit(state.visitedPosDirections[xyToId(state.guard_position_x, state.guard_position_y)], Direction::Left);
					break;
				case Direction::Left:
					state.guard_direction = Direction::Up;
					SetDirectionBit(state.visitedPosDirections[xyToId(state.guard_position_x, state.guard_position_y)], Direction::Up);
					break;
			}
			return StepResult::Ok;
		}
		else
		{
			// Check if loop is found
			if (IsBitSet(state.visitedPosDirections[xyToId(new_pos_x, new_pos_y)], state.guard_direction)) {
				return StepResult::LoopFound;
			}
			// advance if not obstructed
			state.guard_position_x = new_pos_x;
			state.guard_position_y = new_pos_y;
			state.visitedPositions[xyToId(new_pos_x, new_pos_y)] = true;
			SetDirectionBit(state.visitedPosDirections[xyToId(new_pos_x, new_pos_y)], state.guard_direction);
			return StepResult::Ok;
		}
		
	}

	bool PlaceObstruction(State& state, int index) {
		if (xyToId(state.guard_position_x, state.guard_position_y) == index) {
			return false;
		}
		switch (state.map[index]) {
			case MapSquare::Obstruction:
				return false;
			case MapSquare::Free:
				state.map[index] = MapSquare::Obstruction;
				return true;
		}
	}

	bool DoesStateLoop(State& state) {
		auto result = AdvanceState(state);
		while (true) {
			result = AdvanceState(state);
			if (result == StepResult::OutOfBounds) {
				//cout << " out of bounds" << endl;
				return false;
			}
			if (result == StepResult::LoopFound) {
				//cout << " Loops" << endl;
				return true;
			}
		}
	}
}

void
Day_06(const string& input_path)
{
	auto lines = get_input(input_path);

	width = lines[0].size();
	height = lines.size();

	State state_initial;
	// initialize state
	state_initial.map.resize(width * height);
	state_initial.visitedPositions.resize(width * height, false);
	state_initial.visitedPosDirections.resize(width * height, 0);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			auto c = lines[y][x];
			switch (c) {
				case '.':
					state_initial.map[xyToId(x, y)] = MapSquare::Free;
					break;
				case '#':
					state_initial.map[xyToId(x, y)] = MapSquare::Obstruction;
					break;
				case '^':
					state_initial.map[xyToId(x, y)] = MapSquare::Free;
					state_initial.visitedPositions[xyToId(x, y)] = true;
					SetDirectionBit(state_initial.visitedPosDirections[xyToId(x, y)], Direction::Up);
					state_initial.guard_position_x = x;
					state_initial.guard_position_y = y;
					state_initial.guard_direction = Direction::Up;
					break;
				case 'V':
					state_initial.map[xyToId(x, y)] = MapSquare::Free;
					state_initial.visitedPositions[xyToId(x, y)] = true;
					SetDirectionBit(state_initial.visitedPosDirections[xyToId(x, y)], Direction::Down);
					state_initial.guard_position_x = x;
					state_initial.guard_position_y = y;
					state_initial.guard_direction = Direction::Down;
					break;
				case '>':
					state_initial.map[xyToId(x, y)] = MapSquare::Free;
					state_initial.visitedPositions[xyToId(x, y)] = true;
					SetDirectionBit(state_initial.visitedPosDirections[xyToId(x, y)], Direction::Right);
					state_initial.guard_position_x = x;
					state_initial.guard_position_y = y;
					state_initial.guard_direction = Direction::Right;
					break;
				case '<':
					state_initial.map[xyToId(x, y)] = MapSquare::Free;
					state_initial.visitedPositions[xyToId(x, y)] = true;
					SetDirectionBit(state_initial.visitedPosDirections[xyToId(x, y)], Direction::Left);
					state_initial.guard_position_x = x;
					state_initial.guard_position_y = y;
					state_initial.guard_direction = Direction::Left;
					break;
			}
		}
	}

	State state = state_initial;
	while (AdvanceState(state) == StepResult::Ok) {};

	int distinctPositions = count(state.visitedPositions.begin(), state.visitedPositions.end(), true);
	cout << distinctPositions << endl;

	// part 2
	int possibleObstructions = 0;
	for (int i = 0; i < width * height; i++) {
		State state = state_initial;
		if (PlaceObstruction(state, i) == false) {
			continue;
		}
		if (DoesStateLoop(state)) {
			possibleObstructions++;
		}
	}
	cout << possibleObstructions << endl;
}
