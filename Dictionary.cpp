#include <iostream>
#include "Dictionary.h"

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

Dictionary::~Dictionary()
{
}

