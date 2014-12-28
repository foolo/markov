#ifndef UNITTESTS_H
#define	UNITTESTS_H

#include <queue>
#include <iostream>
#include "IFileReader.h"

#define CHECK(A,B) \
	if ((A) != (B)) { \
		std::cerr << "@"<< __LINE__ << ":"; \
		std::cerr << "Expected: (" << #A << " == " << #B << ") Found: (" << (A) << " != " << (B) << ")" << std::endl; \
		exit(1); \
	}

class FileReaderMock : public IFileReader
{
public:
	std::queue<std::string> m_lines;

	bool open(const std::string& filename)
	{
		m_lines.push("det var en gang,"); // 0 1 2 3 4
		m_lines.push("en flicka. hon hette"); // 2 5 6 5 6
		m_lines.push("");
		m_lines.push("");
		m_lines.push("");
		m_lines.push("vad, hon hette."); // 7 4 5 6 4
		return true;
	}

	bool is_open()
	{
		return true;
	}

	bool read_line(std::string& lineOut)
	{
		if (!m_lines.empty())
		{
			lineOut = m_lines.front();
			m_lines.pop();
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
