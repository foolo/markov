#include <vector>
#include <sstream>
#include <string>

#include "Util.h"

std::string Util::IntVecToStr(const std::vector<int>& v) {
	std::ostringstream ss;
	for (auto it = v.begin(); it != v.end(); it++)
	{
		ss << *it << ", ";
	}
	return ss.str();
}

