#include "Dictionary.h"

Dictionary::Dictionary()
{
}

int Dictionary::GetIdForWord(const std::string& newWord)
{
	std::map<std::string, int>::iterator pWordIdPair = m_wordToId.find(newWord);
	
	bool found = (pWordIdPair != m_wordToId.end());
	if (found)
	{
		return pWordIdPair->second;
	}
	else
	{
		int newId = m_wordToId.size();
		m_wordToId[newWord] = newId;
		return newId;
	}
}

Dictionary::~Dictionary()
{
}

