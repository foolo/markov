#include <string>

#ifndef UTIL_H
#define	UTIL_H

class Dictionary;

class Util {
public:
	static std::string IntVecToStr(const std::vector<int>& v);
	static std::string IntVecToIdAndWords(const std::vector<int>& v, Dictionary& dictionary);

private:

};

#endif	/* UTIL_H */

