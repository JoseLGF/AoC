#include <iostream>
#include <vector>
#include <functional>

using namespace std;

//#define TESTING

namespace aoc2025 {
    namespace day01 { void part1(); void part2(); }
    namespace day02 { void part1(); void part2(); }
    namespace day03 { void part1(); void part2(); }
    namespace day04 { void part1(); void part2(); }
    namespace day05 { void part1(); void part2(); }
    namespace day06 { void part1(); void part2(); }
    namespace day07 { void part1(); void part2(); }
    namespace day08 { void part1(); void part2(); }
    namespace day09 { void part1(); void part2(); }
    namespace day10 { void part1(); void part2(); }
}

namespace {
    void NoImpl() {
        cout << "Not Implemented!\n";
    };

    vector<vector<function<void(void)>>> days{
        {aoc2025::day01::part1, aoc2025::day01::part2},
        {aoc2025::day02::part1, aoc2025::day02::part2},
        {aoc2025::day03::part1, aoc2025::day03::part2},
        {aoc2025::day04::part1, aoc2025::day04::part2},
        {aoc2025::day05::part1, aoc2025::day05::part2},
        {aoc2025::day06::part1, aoc2025::day06::part2},
        {aoc2025::day07::part1, aoc2025::day07::part2},
        {aoc2025::day08::part1, aoc2025::day08::part2},
        {aoc2025::day09::part1, aoc2025::day09::part2},
        {aoc2025::day10::part1, aoc2025::day10::part2},
        {NoImpl, NoImpl},
        {NoImpl, NoImpl},
    };
}

int main(int argc, char* argv[])
{
    std::cout << "Advent of code 2025!\n";

#ifdef TESTING
    aoc2025::day01::part1();
    aoc2025::day01::part2();

    aoc2025::day02::part1();
    aoc2025::day02::part2();

    aoc2025::day03::part1();
    aoc2025::day03::part2();

    aoc2025::day04::part1();
    aoc2025::day04::part2();

    aoc2025::day05::part1();
    aoc2025::day05::part2();

    aoc2025::day06::part1();
    aoc2025::day06::part2();

    aoc2025::day07::part1();
    aoc2025::day07::part2();

    aoc2025::day08::part1();
    aoc2025::day08::part2();
#endif
    aoc2025::day09::part1();
    aoc2025::day09::part2();

    //aoc2025::day10::part1();
    //aoc2025::day10::part2();

    const bool runAllDays = false;
    if (runAllDays) {
        for (int i = 0; i < days.size(); i++) {
            auto day = days[i];
            cout << "Day " << ((i <= 9) ? string("0") : string("")) << i+1 << string(" part 1: ");
            day[0]();
            cout << "Day " << ((i <= 9) ? string("0") : string("")) << i+1 << string(" part 2: ");
            day[1]();
        }
    }
}
