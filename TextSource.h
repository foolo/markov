#ifndef TEXTSOURCE_H
#define	TEXTSOURCE_H

#include <vector>

class IFileReader;
class Dictionary;

class TextSource
{
private:
	std::vector<id_t> m_wordIds;
	IFileReader& m_fileReader;
	Dictionary& m_dictionary;

public:
	TextSource(IFileReader& fileReader, Dictionary& dictionary);
	bool LoadText(const std::string& filename);
	std::vector<id_t>& GetWordIds();
	static std::vector<std::string> GetTokensInLine(std::string line);
	static void replaceAll(std::string &s, const std::string &oldValue, const std::string &newValue);
	virtual ~TextSource();

private:
	static void surroundWithSpaces(std::string& s, char c);
};

#endif	/* TEXTSOURCE_H */
