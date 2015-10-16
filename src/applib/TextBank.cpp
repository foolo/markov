#include <string>
#include <boost/algorithm/string.hpp>
#include "ITextSource.h"
#include "TextBank.h"
#include "Dictionary.h"
#include "ITextSource.h"
#include "Util.h"
#include "util/Timer.h"

TextBank::TextBank(ITextSource& fileReader, Dictionary& dictionary) :
m_fileReader(fileReader),
m_dictionary(dictionary)
{
}

void TextBank::ReportProgress()
{
	std::streampos size(m_fileReader.get_size());
	std::streampos position(m_fileReader.get_position());
	int progress = (size != 0) ? (100 * position / size) : 0;
	std::cout << "\rLoaded: " << progress << "%";
	std::cout.flush();
}

bool TextBank::LoadText(const std::string& filename)
{
	if (!m_fileReader.open(filename))
	{
		return false;
	}
	ReportProgress();
	
	Timer timer;
	std::string word;
	while (m_fileReader.read_word(word))
	{
		timer.ReportProgressIfNeeded(800, *this);
		boost::algorithm::trim(word);
		word = Util::ToLowerUtf8(word);
		if (word.empty())
		{
			continue;
		}
		id_t id = m_dictionary.GetIdForWord(word);
		m_wordIds.push_back(id);
	}
	std::cout << std::endl;
	return true;
}

std::vector<id_t>& TextBank::GetWordIds()
{
	return m_wordIds;
}

TextBank::~TextBank()
{
}
