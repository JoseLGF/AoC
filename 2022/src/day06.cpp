#include <string>
#include <iostream>
#include <algorithm>
#include "day06input.h"

using namespace std;

bool distinct(string s) {
    sort(s.begin(), s.end());
    for (int j=1; j<s.size(); j++)
    {
        if (s[j] == s[j-1]) {
            return false;
        }
    }
    return true;
}

int main()
{
    // string input = "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg";

    // Part 1
    for (int i=3; i<input.size(); i++) {
        auto a = input[i];
        auto b = input[i-1];
        auto c = input[i-2];
        auto d = input[i-3];

        if (a == b || a == c || a == d ||
            b == c || b == d ||
            c == d)
        {
            continue;
        }
        cout << "Day 06 part 1:" << to_string(i+1) << endl;
        break;
    }

    // Part 2
    for (int k=13; k<input.size(); k++) {
        string sub_string = input.substr(k-13, 14);

        if (distinct(sub_string)) {
            cout << "Day 06 part 2:" << to_string(k+1) << endl;
            return 0;
        }
        
    }
}