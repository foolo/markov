#include <iostream>
#include "TextRenderer.h"

TextRenderer::TextRenderer() :
m_textState(inital_state)
{
}

bool TextRenderer::IsDelimiter(const std::string s)
{
	return (s == ".") || (s == ",") || (s == "!") || (s == "?");
}

void TextRenderer::HandleWord(const std::string& word)
{
	bool useUpper = false;
	TextState newState = m_textState;
	if (m_textState == inital_state)
	{
		if (IsDelimiter(word))
		{
			newState = sentence_ended;
		}
		else
		{
			useUpper = true;
			newState = middle_of_sentence;
		}
	}
	else if (m_textState == middle_of_sentence)
	{
		if (IsDelimiter(word))
		{
			newState = sentence_ended;
		}
		else
		{
			std::cout << " ";
		}
	}
	else // m_textState == sentence_ended
	{
		if (!IsDelimiter(word))
		{
			std::cout << " ";
			useUpper = true;
			newState = middle_of_sentence;
		}
	}
	m_textState = newState;
	std::cout << word;
}

void TextRenderer::Render(const std::vector<id_t>& ids, Dictionary& dictionary)
{
	std::cout << "Renderign" << ids.size() << std::endl;
	for (auto pId = ids.begin(); pId != ids.end(); pId++)
	{
		std::string newWord = dictionary.SearchWordForId(*pId);
		HandleWord(newWord);
	}
}

TextRenderer::~TextRenderer()
{
}
