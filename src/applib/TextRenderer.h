#ifndef TEXTRENDERER_H
#define	TEXTRENDERER_H

#include <vector>
#include <string>
#include "Dictionary.h"
#include "Types.h"

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

#endif	/* TEXTRENDERER_H */
