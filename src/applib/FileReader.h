#ifndef FILEREADER_H
#define	FILEREADER_H

#include <fstream>
#include "ITextSource.h"
#include <vector>
#include <string>

class FileReader : public ITextSource
{
private:
	std::ifstream m_ifstream;
	std::vector<std::string> m_currentLine;
	std::vector<std::string>::iterator m_currentWordInLine;
	std::streampos m_size;

public:
	FileReader();
	virtual ~FileReader();
	virtual bool open(const std::string& filename);
	virtual bool is_open();
	virtual bool read_word(std::string& wordOut);
	virtual std::streampos get_size();
	virtual std::streampos get_position();

	static std::vector<std::string> GetTokensInLine(std::string line);
	static void replaceAll(std::string &s, const std::string &oldValue, const std::string &newValue);

private:
	static void surroundWithSpaces(std::string& s, char c);
	static void removeOccurances(std::string& s, char c);

};

#endif	/* FILEREADER_H */
