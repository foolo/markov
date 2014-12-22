#include <iostream>
#include "Dictionary.h"

Dictionary::Dictionary()
{
}

int Dictionary::GetIdForWord(const std::string& newWord)
{

	// TODO can be simplified to just a map lookup, and then check if result is 0

	std::map<std::string, int>::iterator pWordIdPair = m_wordToId.find(newWord);

	bool found = (pWordIdPair != m_wordToId.end());
	if (found)
	{
		//std::cout << "Found " << newWord << "  =  " << pWordIdPair->second << std::endl;
		return pWordIdPair->second;
	}
	else
	{
		int newId = m_wordToId.size();
		//std::cout << "Adding " << newWord << "  =  " << newId << std::endl;
		m_wordToId[newWord] = newId;
		return newId;
	}
}

std::string Dictionary::SearchWordForId(int idToFind)
{
	for (auto pWordId = m_wordToId.begin(); pWordId != m_wordToId.end(); ++pWordId)
		if (pWordId->second == idToFind)
		{
			return pWordId->first;
		}
	return "ID NOT FOUND";
}

Dictionary::~Dictionary()
{
}

