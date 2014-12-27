#include <vector>
#include <sstream>
#include <string>

#include "Util.h"
#include "Dictionary.h"

std::string Util::IntVecToStr(const std::vector<int>& v) {
	std::ostringstream ss;
	for (auto it = v.begin(); it != v.end(); it++)
	{
		ss << *it << ",";
	}
	return ss.str();
}

std::string Util::IntVecToIdAndWords(const std::vector<int>& v, Dictionary& dictionary)
{
	std::ostringstream ss;
	for (auto pId = v.begin(); pId != v.end(); pId++)
	{
		ss << dictionary.SearchWordForId(*pId) << "(" << *pId << ") ";
	}
	return ss.str();

}
