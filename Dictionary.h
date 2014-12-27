#ifndef DICTIONARY_H
#define	DICTIONARY_H

#include <map>
#include <string>

typedef unsigned id_t;

class Dictionary
{
private:
	std::map<std::string, id_t> m_wordToId;

public:
	Dictionary();
	id_t GetIdForWord(const std::string& newWord);
	std::string SearchWordForId(id_t idToFind);
	virtual ~Dictionary();
};

#endif	/* DICTIONARY_H */

