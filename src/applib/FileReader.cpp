#include <boost/algorithm/string.hpp>
#include "FileReader.h"

FileReader::FileReader() :
m_currentWordInLine(m_currentLine.end())
{
}

bool FileReader::open(const std::string& filename)
{
	m_ifstream.close();
	m_ifstream.open(filename.c_str());
	return m_ifstream.is_open();
}

bool FileReader::is_open()
{
	return m_ifstream.is_open();
}

bool FileReader::read_word(std::string& wordOut)
{
	if (m_currentWordInLine == m_currentLine.end())
	{
		m_currentLine.clear();
		while(m_currentLine.empty())
		{
			std::string line;
			bool readRes = getline(m_ifstream, line);
			if (!readRes)
			{
				return false;
			}
			m_currentLine = GetTokensInLine(line);
		}
		m_currentWordInLine = m_currentLine.begin();
	}
	wordOut = *(m_currentWordInLine++);
	return true;
}

std::vector<std::string> FileReader::GetTokensInLine(std::string line)
{
	std::string specialCharacters(".,!?");
	for (auto pC = specialCharacters.begin(); pC != specialCharacters.end(); pC++)
	{
		surroundWithSpaces(line, *pC);
	}

	std::string ignoreCharacters("%&/()[]{}#=;:_|<>*~^£$+'`´\"«»");
	for (auto pC = ignoreCharacters.begin(); pC != ignoreCharacters.end(); pC++)
	{
		removeOccurances(line, *pC);
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

void FileReader::surroundWithSpaces(std::string& s, char c)
{
	std::string oldString(1, c);
	std::string newString = std::string(" ") + oldString + " ";
	replaceAll(s, oldString, newString);
}

void FileReader::removeOccurances(std::string& s, char c)
{
	std::string oldString(1, c);
	std::string newString = "";
	replaceAll(s, oldString, newString);
}

void FileReader::replaceAll(std::string& s, const std::string& oldValue, const std::string& newValue)
{
	for (size_t pos = 0;; pos += newValue.length())
	{
		pos = s.find(oldValue, pos);
		if (pos == std::string::npos) break;
		s.erase(pos, oldValue.length());
		s.insert(pos, newValue);
	}
}

FileReader::~FileReader()
{
}
