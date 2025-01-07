#include "day13.h"
#include "common.h"

#include <iostream>
#include <regex>

using namespace std;

namespace
{
	const int kA_buttonCostTokens = 3;
	const int kB_buttonCostTokens = 1;
	const int kMaxButtonPresses = 100;

	struct ClawMachine {
		int AX;
		int AY;
		int BX;
		int BY;
		int TX;
		int TY;

		ClawMachine(int ax, int ay, int bx, int by, int tx, int ty)
		: AX{ax}
		, AY{ay}
		, BX{bx}
		, BY{by}
		, TX{tx}
		, TY{ty}
		{ }
	};

	pair<int, int> FindXYInStr(const string& str) {
		const regex xyreg(R"(X[\+=](\d+).+Y[\+=](\d+))", regex_constants::ECMAScript);
		auto xy_it = sregex_iterator(str.begin(), str.end(), xyreg);
		auto xy_end = sregex_iterator();

		auto xmatch = *xy_it;
		auto xstr = xmatch[1].str();
		//cout << "xstr: " << xstr << endl;
		int x = stoi(xstr);

		auto ymatch = *xy_it;
		auto ystr = ymatch[2].str();
		//cout << "ystr: " << ystr << endl;
		int y = stoi(ystr);

		return make_pair(x, y);
	}

	int ExpandMachine(const ClawMachine& machine, int current_tokens, int current_button_presses, int currentX, int currentY) {
		// Target reached
		if (currentX == machine.TX && currentY == machine.TY) {
			return current_tokens;
		}

		// target overshoot
		if (currentX > machine.TX || currentY == machine.TY) {
			return numeric_limits<int>::max();
		}

		// max buttons pressed
		if (current_button_presses >= kMaxButtonPresses) {
			return numeric_limits<int>::max();
		}

		int a_tokens = numeric_limits<int>::max();
		int b_tokens = numeric_limits<int>::max();
		// expand A
		a_tokens = ExpandMachine(machine,
									 current_tokens + kA_buttonCostTokens,
			                         current_button_presses+1,
			                         currentX+machine.AX,
									 currentY+machine.AY);
		// expand B
		b_tokens = ExpandMachine(machine,
									 current_tokens + kB_buttonCostTokens,
									 current_button_presses + 1,
									 currentX + machine.BX,
									 currentY + machine.BY);

		return min(a_tokens, b_tokens);
	}

	int CalculateMinTokensForPrizeWin(const ClawMachine& machine) {
		return ExpandMachine(machine, 0, 0, 0, 0);
	}
}

void
Day_13(const string& input_path)
{
	auto lines = get_input(input_path);

	vector<ClawMachine> clawMachines;

	int i = 0;
	while (i < lines.size()) {
		auto line1 = lines[i];
		int ax;
		int ay;
		auto axy = FindXYInStr(line1);
		ax = axy.first;
		ay = axy.second;
		i++;
		auto line2 = lines[i];
		int bx;
		int by;
		auto bxy = FindXYInStr(line2);
		bx = bxy.first;
		by = bxy.second;
		i++;
		auto line3 = lines[i];
		int tx;
		int ty;
		auto txy = FindXYInStr(line3);
		tx = txy.first;
		ty = txy.second;
		i++;// blank line
		i++;

		clawMachines.push_back(ClawMachine{ax, ay, bx, by, tx, ty});
	}

	// print clawmachines
	for (auto& cm : clawMachines) {
		cout << cm.AX << "," << cm.AY << endl;
		cout << cm.BX << "," << cm.BY << endl;
		cout << cm.TX << "," << cm.TY << endl;
		cout << "Min tokens: " << endl;
		cout << CalculateMinTokensForPrizeWin(cm) << endl;
	}


}
