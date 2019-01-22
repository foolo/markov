#include "Dictionary.h"
#include "util/SerializeUtils.h"

Dictionary::Dictionary()
{
}

id_t Dictionary::GetIdForWord(const std::string& newWord)
{
	auto pWordIdPair = m_wordToId.find(newWord);
	if (pWordIdPair != m_wordToId.end())
	{
		return pWordIdPair->second;
	}
	else
	{
		id_t newId = m_wordToId.size();
		m_wordToId[newWord] = newId;
		return newId;
	}
}

std::string Dictionary::SearchWordForId(id_t idToFind)
{
	for (auto pWordId = m_wordToId.begin(); pWordId != m_wordToId.end(); ++pWordId)
	{
		if (pWordId->second == idToFind)
		{
			return pWordId->first;
		}
	}
	return "ID NOT FOUND";
}

void Dictionary::serialize(std::ostream& s)
{
	s << "words ";
	s << m_wordToId.size() << std::endl;
	for (auto itr = m_wordToId.begin(); itr != m_wordToId.end(); ++itr) {
		std::string word = itr->first;
		id_t id = itr->second;
		s << word << " " << id << std::endl;
	}
}

Dictionary Dictionary::deserialize(std::istream& s) {
	SerializeUtils::assert(s, "words");
	size_t size = SerializeUtils::read_unsigned_long(s);
	Dictionary dictionary;
	for (size_t i = 0; i < size; i++) {
		std::string word = SerializeUtils::read_string(s);
		id_t id = SerializeUtils::read_unsigned(s);
		dictionary.m_wordToId[word] = id;
	}
	return dictionary;
}

Dictionary::~Dictionary()
{
}
