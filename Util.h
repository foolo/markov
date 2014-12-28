#ifndef UTIL_H
#define	UTIL_H

#include <string>
#include <vector>

class Dictionary;

class Util
{
public:
	static std::string IdVecToStr(const std::vector<id_t>& v);
	static std::string IdVecToIdAndWords(const std::vector<id_t>& v, Dictionary& dictionary);
};

#endif	/* UTIL_H */
