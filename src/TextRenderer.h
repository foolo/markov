#pragma once

#include <vector>
#include <string>
#include "Types.h"

class Dictionary;

class TextRenderer
{
private:
	TextState m_textState;

public:
	TextRenderer();
	void Render(const std::vector<id_t>& ids, Dictionary& dictionary);
	virtual ~TextRenderer();

private:
	bool IsDelimiter(const std::string s);
	void HandleWord(std::string word);
};
