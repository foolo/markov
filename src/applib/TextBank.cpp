#include <string>
#include <boost/algorithm/string.hpp>
#include "TextBank.h"
#include "Dictionary.h"
#include "ITextSource.h"
#include "Util.h"

TextBank::TextBank(ITextSource& fileReader, Dictionary& dictionary) :
m_fileReader(fileReader),
m_dictionary(dictionary)
{
}

bool TextBank::LoadText(const std::string& filename)
{
	if (!m_fileReader.open(filename))
	{
		return false;
	}

	std::string word;
	while (m_fileReader.read_word(word))
	{
		boost::algorithm::trim(word);
		word = Util::ToLowerUtf8(word);
		if (word.empty())
		{
			continue;
		}
		id_t id = m_dictionary.GetIdForWord(word);
		m_wordIds.push_back(id);
	}
	return true;
}

std::vector<id_t>& TextBank::GetWordIds()
{
	return m_wordIds;
}

TextBank::~TextBank()
{
}
