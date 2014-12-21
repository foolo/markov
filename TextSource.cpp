#include <string>
#include <sstream>
#include <iostream>
#include "TextSource.h"
#include "Dictionary.h"
#include "IFileReader.h"

TextSource::TextSource(IFileReader& fileReader, Dictionary& dictionary) :
m_fileReader(fileReader),
m_dictionary(dictionary)
{
}

bool TextSource::LoadText(const std::string& filename)
{
	if (!m_fileReader.open(filename))
	{
		std::cerr << "Could not open " << filename << "." << std::endl;
		return false;
	}

	std::string line;
	while (m_fileReader.read_line(line))
	{
		std::vector<std::string> words = GetTokensInLine(line);
		for (auto pWord = words.begin(); pWord != words.end(); pWord++)
		{
			int id = m_dictionary.GetIdForWord(*pWord);
			m_wordIds.push_back(id);
		}
	}

	return true;
}

std::vector<std::string> TextSource::GetTokensInLine(std::string line)
{
	replaceAll(line, ".", " . ");
	std::vector<std::string> splitStrings = Split(line, ' ');
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

std::vector<std::string> TextSource::Split(const std::string& s, char delimiter)
{
	std::vector<std::string> elements;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delimiter))
	{
		elements.push_back(item);
	}
	return elements;
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

