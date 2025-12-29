#pragma once

#include<vector>
#include<string>

typedef uint64_t u64;
typedef uint32_t u32;
typedef int64_t  i64;

std::vector<std::string> get_input(int day, bool test = false);
std::vector<std::string> split_line(const std::string& str, const char delimiter = ',');

inline bool isDigit(const char c) { return c >= '0' && c <= '9'; }