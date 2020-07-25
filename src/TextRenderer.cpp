#include <iostream>
#include "TextRenderer.h"
#include "Util.h"
#include "Dictionary.h"

TextRenderer::TextRenderer() :
m_textState(inital_state)
{
}

bool TextRenderer::IsDelimiter(const std::string s)
{
	return (s == ".") || (s == "!") || (s == "?");
}

void TextRenderer::HandleWord(std::string word)
{
	bool useUpper = false;
	TextState newState = m_textState;
	if (m_textState == inital_state)
	{
		if (IsDelimiter(word))
		{
			newState = sentence_ended;
		}
		else if (word == ",")
		{
			newState = sentence_pause;
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
		else if (word == ",")
		{
			newState = sentence_pause;
		}
		else
		{
			std::cout << " ";
		}
	}
	else if (m_textState == sentence_pause)
	{
		if (!IsDelimiter(word))
		{
			std::cout << " ";
			newState = middle_of_sentence;
		}
		else if (word == ",")
		{
			newState = sentence_pause;
		}
		else
		{
			newState = sentence_ended;
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
		else if (word == ",")
		{
			newState = sentence_pause;
		}
	}
	m_textState = newState;
	if (useUpper)
	{
		word = Util::Capitalize(word);
	}

	std::cout << word;
}

void TextRenderer::Render(const std::vector<id_t>& ids, Dictionary& dictionary)
{
	std::cout << "Rendering " << ids.size() << std::endl;
	for (auto pId = ids.begin(); pId != ids.end(); pId++)
	{
		std::string newWord = dictionary.SearchWordForId(*pId);
		HandleWord(newWord);
	}
	std::cout << std::endl;
}

TextRenderer::~TextRenderer()
{
}
