#include <vector>
#include <sstream>
#include <string>
#include "Util.h"
#include "Dictionary.h"

std::string Util::IdVecToStr(const std::vector<id_t>& v)
{
	std::ostringstream ss;
	for (auto it = v.begin(); it != v.end(); it++)
	{
		ss << *it << ",";
	}
	return ss.str();
}

std::string Util::IdVecToIdAndWords(const std::vector<id_t>& v, Dictionary& dictionary)
{
	std::ostringstream ss;
	for (auto pId = v.begin(); pId != v.end(); pId++)
	{
		ss << dictionary.SearchWordForId(*pId) << "(" << *pId << ") ";
	}
	return ss.str();
}
