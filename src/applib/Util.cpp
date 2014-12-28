#include <vector>
#include <sstream>
#include <string>
#include <cstring>
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

std::wstring Util::MultibyteToWideString(const char* ptr)
{
	std::wstring s;
	std::mbtowc(NULL, 0, 0); // reset the conversion state
	const char* end = ptr + std::strlen(ptr);
	int ret;
	for (wchar_t wc; (ret = std::mbtowc(&wc, ptr, end - ptr)) > 0; ptr += ret)
	{
		s.push_back(wc);
	}
	return s;
}

std::string Util::WideStringToMultibyte(const std::wstring& wstr)
{
	std::string s;
	std::mbstate_t state = std::mbstate_t();
	for (wchar_t wc : wstr)
	{
		std::string mb(MB_CUR_MAX, '\0');
		std::wcrtomb(&mb[0], wc, &state);
		s.append(mb.c_str());
	}
	return s;
}

std::string Util::ToUpperUtf8(const std::string& s)
{
	std::wstring wideStr = MultibyteToWideString(s.c_str());
	for (auto it = wideStr.begin(); it != wideStr.end(); it++)
	{
		*it = towupper(*it);
	}
	return WideStringToMultibyte(wideStr);
}

std::string Util::ToLowerUtf8(const std::string& s)
{
	std::wstring wideStr = MultibyteToWideString(s.c_str());
	for (auto it = wideStr.begin(); it != wideStr.end(); it++)
	{
		*it = towlower(*it);
	}
	return WideStringToMultibyte(wideStr);
}

std::string Util::Capitalize(const std::string& s)
{
	std::wstring wideStr(MultibyteToWideString(s.c_str()));

	if (!wideStr.empty())
	{
		wideStr.at(0) = towupper(wideStr.at(0));
	}
	return WideStringToMultibyte(wideStr);
}
