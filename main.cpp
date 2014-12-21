#include <iostream>
#include <queue>
#include "TextSource.h"
#include "IFileReader.h"
#include "MarkovChain.h"


#define CHECK(A,B) \
	if ((A) != (B)) { \
		std::cerr << "@"<< __LINE__ << ":"; \
		std::cerr << "Expected: (" << #A << " == " << #B << ") Found: (" << (A) << " != " << (B) << ")" << std::endl; \
		exit(1); \
	}

class FileReaderMock : public IFileReader {
public:

	std::queue<std::string> m_lines;

	bool open(const std::string& filename)
	{
		m_lines.push("det var en gang,"); // 0 1 2 3 4
		m_lines.push("en flicka. hon hette"); // 2 5 6 5 6
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

void runtests()
{
	{
		CHECK(MarkovState(std::vector<int>({1, 2, 3})) < MarkovState(std::vector<int>({1, 2, 4})), true)
		CHECK(MarkovState(std::vector<int>({5, 6})) < MarkovState(std::vector<int>({3, 2, 1})), true)
		CHECK(MarkovState(std::vector<int>({5})) < MarkovState(std::vector<int>({1, 2, 3})), true)
		CHECK(MarkovState(std::vector<int>({1, 2, 3})) < MarkovState(std::vector<int>({1, 2, 3, 1})), true)

		CHECK(MarkovState(std::vector<int>({1, 2, 4})) < MarkovState(std::vector<int>({1, 2, 3})), false)
		CHECK(MarkovState(std::vector<int>({3, 2, 1})) < MarkovState(std::vector<int>({5, 6})), false)
		CHECK(MarkovState(std::vector<int>({1, 2, 3})) < MarkovState(std::vector<int>({5})), false)
		CHECK(MarkovState(std::vector<int>({1, 2, 3, 1})) < MarkovState(std::vector<int>({1, 2, 3})), false)

		CHECK(MarkovState(std::vector<int>({4, 2, 7})) < MarkovState(std::vector<int>({4, 2, 7})), false)

		CHECK(MarkovState(std::vector<int>({5})) < MarkovState(std::vector<int>({5})), false)
		CHECK(MarkovState(std::vector<int>({})) < MarkovState(std::vector<int>({})), false)

		CHECK(MarkovState(std::vector<int>({8, 2, 3})) < MarkovState(std::vector<int>({9, 2, 3})), true)
		CHECK(MarkovState(std::vector<int>({8, 2, 4})) < MarkovState(std::vector<int>({8, 3, 3})), true)
		CHECK(MarkovState(std::vector<int>({9, 2, 3})) < MarkovState(std::vector<int>({8, 2, 3})), false)
		CHECK(MarkovState(std::vector<int>({8, 3, 3})) < MarkovState(std::vector<int>({8, 2, 4})), false)
	}

	{
		Dictionary dictionary;
		FileReaderMock mockFileReader;
		TextSource textSource(mockFileReader, dictionary);
		textSource.LoadText("");
		auto ids = textSource.GetWordIds();
		int i = 0;
		CHECK(ids.size(), 15);
		// line 1
		CHECK(ids.at(i++), 0); // det
		CHECK(ids.at(i++), 1); // var
		CHECK(ids.at(i++), 2); // en
		CHECK(ids.at(i++), 3); // gang
		CHECK(ids.at(i++), 4); // ,
		// line 2
		CHECK(ids.at(i++), 2); // en
		CHECK(ids.at(i++), 5); // flicka
		CHECK(ids.at(i++), 6); // .
		CHECK(ids.at(i++), 7); // hon
		CHECK(ids.at(i++), 8); // hette
		// line 3
		CHECK(ids.at(i++), 9); // vad
		CHECK(ids.at(i++), 4); // ,
		CHECK(ids.at(i++), 7); // hon
		CHECK(ids.at(i++), 8); // hette
		CHECK(ids.at(i++), 6); // .
	}

	{
		std::vector<std::string> result = TextSource::Split("test  split a string.that, is amazing", ' ');
		CHECK(result.size(), 7);
		int i = 0;
		CHECK(result.at(i++), "test");
		CHECK(result.at(i++), "");
		CHECK(result.at(i++), "split");
		CHECK(result.at(i++), "a");
		CHECK(result.at(i++), "string.that,");
		CHECK(result.at(i++), "is");
		CHECK(result.at(i++), "amazing");
	}
	{
		std::vector<std::string> result = TextSource::GetTokensInLine("test  split a string.that, is amazing");
		CHECK(result.size(), 9);
		int i = 0;
		CHECK(result.at(i++), "test");
		CHECK(result.at(i++), "split");
		CHECK(result.at(i++), "a");
		CHECK(result.at(i++), "string");
		CHECK(result.at(i++), ".");
		CHECK(result.at(i++), "that");
		CHECK(result.at(i++), ",");
		CHECK(result.at(i++), "is");
		CHECK(result.at(i++), "amazing");
	}

	{
		std::string s = "what is this ";
		TextSource::replaceAll(s, "i", "siri");
		CHECK(s, "what siris thsiris ");
	}
}

int main(int argc, char* argv[])
{
	runtests();
	std::cout << "TESTS PASSED" << std::endl;


	if (argc < 2)
	{
		std::cerr << "missing filename argument" << std::endl;
	}


	return 0;
}
