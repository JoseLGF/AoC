#pragma once

#include <string>
#include <iostream>

class Logger
{
public:
	Logger(std::string moduleName, bool enabled = false)
	: mModuleName(moduleName)
	, mEnabled(enabled)
	{ }

	void info(const std::string& s) {
		if (mEnabled) {
			std::cout << mModuleName << ": " << s << std::endl;
		}
	}

private:
	const std::string mModuleName;
	const bool mEnabled;
};
