#pragma once

#include <map>
#include <string>
#include <ostream>
#include <istream>

typedef std::map<std::string, id_t> WordIdMap_t;

class Dictionary
{
private:
	WordIdMap_t m_wordToId;

public:
	Dictionary();
	id_t GetIdForWord(const std::string& newWord);
	std::string SearchWordForId(id_t idToFind);
	void serialize(std::ostream &s);
	static Dictionary deserialize(std::istream &s);
	virtual ~Dictionary();
};
