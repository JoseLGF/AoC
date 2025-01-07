#include "day09.h"
#include "common.h"

#include <iostream>
#include <algorithm>

using namespace std;

namespace
{
	const bool kFreeSpace = false;
	const bool kFileSpace = true;
	const int kFreeSpaceId = -1;

	void print_disk(const vector<int>& disk) {
		for (auto& block : disk) {
			if (block < 0) {
				cout << '.';
			}
			else {
				cout << block;
			}
		}
		cout << endl;
	}

	vector<int> decompress_disk_map(const string& dense_map) {
		vector<int> decompressed_disk;
		bool current_space = kFileSpace;
		int current_block_id = 0;
		for (auto& c : dense_map) {
			int block_length = c - '0';
			for (int i = 0; i < block_length; i++) {
				if (current_space == kFreeSpace) {
					decompressed_disk.push_back(kFreeSpaceId);
				}
				else {
					decompressed_disk.push_back(current_block_id);
				}
			}
			if (current_space == kFileSpace) {
				current_block_id++;
			}
			current_space = !current_space;
		}

		return decompressed_disk;
	}

	void rearrange_file_blocks_part1(vector<int>& disk) {
		auto left_it = disk.begin();
		auto right_it = disk.end();
		right_it--;

		auto advance_left = [&] () {
			while (left_it != disk.end() && *left_it != kFreeSpaceId) left_it++;
		};
		auto advance_right = [&]() {
			while (right_it > disk.begin() && *right_it == kFreeSpaceId) right_it--;
		};

		while (left_it < right_it) {
			advance_left();
			advance_right();
			if (left_it < right_it) {
				swap(*left_it, *right_it);
			}
		}
	}

	void rearrange_file_blocks_part2(vector<int>& disk) {
		auto left_it = disk.begin();
		auto right_it = disk.end();
		right_it--;

		int max_disk_block_id = *max_element(disk.begin(), disk.end());

		auto find_id_range_in_disk = [&](int id) {
			auto left = find(disk.begin(), disk.end(), id);
			auto right = find(disk.rbegin(), disk.rend(), id);
			pair<int, int> out{ distance(disk.begin(), left) , distance(left, right.base())};
			return out;
		};

		auto find_free_blocks = [&]() {
			vector<pair<int, int>> free_blocks;
			bool previous_free = false;
			int current_block_index = 0;
			int current_block_size = 0;
			for (int i = 0; i < disk.size(); i++) {
				// free
				if (disk[i] < 0) {
					if (previous_free) {
						current_block_size++;
					}
					else {
						current_block_index = i;
						current_block_size = 1;
						previous_free = true;
					}
				}
				// not free
				else {
					if (previous_free) {
						free_blocks.push_back(make_pair(current_block_index, current_block_size));
						previous_free = false;
					}
					else {
						// do nothing
					}
				}
			}

			return free_blocks;
		};

		auto transfer_blocks = [&](int source_start, int dest_start, int n) {
			for (int i = 0; i < n; i++) {
				swap(disk[source_start + i], disk[dest_start + i]);
			}
		};

		for (auto id = max_disk_block_id; id >= 0; id--) {
			// find the range of blocks with given id
			auto [block_start, block_length] = find_id_range_in_disk(id);
			auto free_blocks = find_free_blocks();
			for (auto& block : free_blocks) {
				if (block_start > block.first && block.second >= block_length) {
					transfer_blocks(block_start, block.first, block_length);
					continue;
				}
			}
		}
	}

	long long int filesystem_checksum(vector<int> disk) {
		long long int checksum = 0;
		for (int i = 0; i < disk.size(); i++) {
			int block_id = disk[i];
			if (block_id >= 0) {
				checksum += block_id * i;
			}
		}
		return checksum;
	}

	void Part1(vector<int> disk) {
		rearrange_file_blocks_part1(disk);
		cout << filesystem_checksum(disk) << endl;
	}

	void Part2(vector<int> disk) {
		rearrange_file_blocks_part2(disk);
		cout << filesystem_checksum(disk) << endl;
	}
}

void
Day_09(const string& input_path)
{
	auto line = get_input_string(input_path);

	auto decompressed_disk = decompress_disk_map(line);
	Part1(decompressed_disk);
	Part2(decompressed_disk);
}
