#ifndef TEXTSOURCE_H
#define	TEXTSOURCE_H

#include <vector>

class ITextSource;
class Dictionary;

class TextBank
{
private:
	std::vector<id_t> m_wordIds;
	ITextSource& m_fileReader;
	Dictionary& m_dictionary;

public:
	TextBank(ITextSource& fileReader, Dictionary& dictionary);
	bool LoadText(const std::string& filename);
	std::vector<id_t>& GetWordIds();
	static std::vector<std::string> GetTokensInLine(std::string line);
	static void replaceAll(std::string &s, const std::string &oldValue, const std::string &newValue);
	virtual ~TextBank();

private:
	static void surroundWithSpaces(std::string& s, char c);
};

#endif	/* TEXTSOURCE_H */
