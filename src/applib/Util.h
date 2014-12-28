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
	static std::wstring MultibyteToWideString(const char* ptr);
	static std::string WideStringToMultibyte(const std::wstring& wstr);
	static std::string ToUpperUtf8(const std::string& s);
	static std::string ToLowerUtf8(const std::string& s);
	static std::string Capitalize(const std::string& s);
};

#endif	/* UTIL_H */
