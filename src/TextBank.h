#pragma once

#include <vector>
#include <string>
#include "util/IProgressReporter.h"

class ITextSource;
class Dictionary;

class TextBank : IProgressReporter
{
private:
	std::vector<id_t> m_wordIds;
	ITextSource& m_fileReader;
	Dictionary& m_dictionary;

public:
	TextBank(ITextSource& fileReader, Dictionary& dictionary);
	bool LoadText(const std::string& filename);
	std::vector<id_t>& GetWordIds();
	virtual ~TextBank();
	void ReportProgress();
};
