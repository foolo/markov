#ifndef UNITTESTS_H
#define	UNITTESTS_H

#include <queue>
#include <iostream>
#include "ITextSource.h"

#define CHECK(A,B) \
	if ((A) != (B)) { \
		std::cerr << "@"<< __LINE__ << ":"; \
		std::cerr << "Expected: (" << #A << " == " << #B << ") Found: (" << (A) << " != " << (B) << ")" << std::endl; \
		exit(1); \
	}

class FileReaderMock : public ITextSource
{
public:
	std::queue<std::string> m_words;

	bool open(const std::string& filename)
	{
		m_words.push("det"); // 0
		m_words.push("var "); // 1
		m_words.push(" en "); // 2
		m_words.push("gang"); // 3
		m_words.push("  ,"); // 4

		m_words.push("en"); // 2
		m_words.push(" flicka"); // 5
		m_words.push("."); // 6
		m_words.push("hon "); // 5
		m_words.push("hette"); // 6
		m_words.push("");
		m_words.push("");
		m_words.push("");
		m_words.push("vad"); // 7
		m_words.push(","); // 4
		m_words.push(" hon"); // 5
		m_words.push(" hette"); // 6
		m_words.push("."); // 4
		return true;
	}

	bool is_open()
	{
		return true;
	}

	bool read_word(std::string& wordOut)
	{
		if (!m_words.empty())
		{
			wordOut = m_words.front();
			m_words.pop();
			return true;
		}
		return false;
	}
};

class UnitTests
{
public:
	static void Run();
};

#endif	/* UNITTESTS_H */
