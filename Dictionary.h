#ifndef DICTIONARY_H
#define	DICTIONARY_H

#include <map>
#include <string>

class Dictionary
{
private:
	std::map<std::string, int> m_wordToId;

public:
	Dictionary();
	int GetIdForWord(const std::string& newWord);

	std::string SearchWordForId(int idToFind);

	virtual ~Dictionary();
private:

};

#endif	/* DICTIONARY_H */

