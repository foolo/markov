#include <string>
#include <boost/algorithm/string.hpp>
#include "TextSource.h"
#include "Dictionary.h"
#include "IFileReader.h"

TextSource::TextSource(IFileReader& fileReader, Dictionary& dictionary) :
m_fileReader(fileReader),
m_dictionary(dictionary)
{
}

std::wstring MultibyteToWideString(const char* ptr)
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

std::string WideStringToMultibyte(const std::wstring& wstr)
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

std::string ToUpperUtf8(std::string& s)
{
	std::wstring wideStr = MultibyteToWideString(s.c_str());
	for (auto it = wideStr.begin(); it != wideStr.end(); it++)
	{
		*it = towupper(*it);
	}
	return WideStringToMultibyte(wideStr);
}

bool TextSource::LoadText(const std::string& filename)
{
	if (!m_fileReader.open(filename))
	{
		return false;
	}

	std::string line;
	while (m_fileReader.read_line(line))
	{
		std::vector<std::string> words = GetTokensInLine(line);
		for (auto pWord = words.begin(); pWord != words.end(); pWord++)
		{
			boost::algorithm::trim(*pWord);
			*pWord = ToUpperUtf8(*pWord);
			id_t id = m_dictionary.GetIdForWord(*pWord);
			m_wordIds.push_back(id);
		}
	}
	return true;
}

std::vector<id_t>& TextSource::GetWordIds()
{
	return m_wordIds;
}

void TextSource::surroundWithSpaces(std::string& s, char c)
{
	std::string oldString(1, c);
	std::string newString = std::string(" ") + oldString + " ";
	replaceAll(s, oldString, newString);
}

std::vector<std::string> TextSource::GetTokensInLine(std::string line)
{
	std::string specialCharacters(".,!\"%&/()=?£$+'");
	for (auto pC = specialCharacters.begin(); pC != specialCharacters.end(); pC++)
	{
		surroundWithSpaces(line, *pC);
	}
	std::vector<std::string> splitStrings;
	boost::split(splitStrings, line, boost::is_any_of(" "));

	std::vector<std::string> resultTokens;
	for (auto pWord = splitStrings.begin(); pWord != splitStrings.end(); pWord++)
	{
		if (!pWord->empty())
		{
			resultTokens.push_back(*pWord);
		}
	}
	return resultTokens;
}

void TextSource::replaceAll(std::string& s, const std::string& oldValue, const std::string& newValue)
{
	for (size_t pos = 0;; pos += newValue.length())
	{
		pos = s.find(oldValue, pos);
		if (pos == std::string::npos) break;
		s.erase(pos, oldValue.length());
		s.insert(pos, newValue);
	}
}

TextSource::~TextSource()
{
}