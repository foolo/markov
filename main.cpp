#include <iostream>
#include <queue>
#include <iterator>
#include "TextSource.h"
#include "IFileReader.h"
#include "MarkovChain.h"
#include "FileReader.h"


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

	// Test MarkovChain::GetRange
	{
		MarkovChain markovChain(3);
		markovChain.RegisterState(std::vector<int>({3, 5, 1}));

		StateRange stateRange = markovChain.GetRange(std::vector<int>({3, 5}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 1);

		markovChain.RegisterState(std::vector<int>({3, 5, 4}));
		markovChain.RegisterState(std::vector<int>({3, 5, 1}));
		markovChain.RegisterState(std::vector<int>({3, 5, 4}));
		markovChain.RegisterState(std::vector<int>({3, 5, 5}));
		markovChain.RegisterState(std::vector<int>({3, 5, 5}));
		markovChain.RegisterState(std::vector<int>({3, 5, 1}));

		markovChain.RegisterState(std::vector<int>({9, 8, 4}));
		markovChain.RegisterState(std::vector<int>({9, 8, 1}));
		markovChain.RegisterState(std::vector<int>({9, 8, 4}));
		markovChain.RegisterState(std::vector<int>({9, 8, 5}));
		markovChain.RegisterState(std::vector<int>({9, 8, 5}));
		markovChain.RegisterState(std::vector<int>({9, 8, 9}));
		markovChain.RegisterState(std::vector<int>({9, 8, 9}));
		markovChain.RegisterState(std::vector<int>({9, 8, 9}));
		markovChain.RegisterState(std::vector<int>({9, 8, 1}));
		markovChain.RegisterState(std::vector<int>({9, 8, 1}));
		markovChain.RegisterState(std::vector<int>({9, 8, 4}));
		markovChain.RegisterState(std::vector<int>({9, 8, 4}));
		markovChain.RegisterState(std::vector<int>({9, 8, 5}));
		markovChain.RegisterState(std::vector<int>({9, 8, 7}));
		markovChain.RegisterState(std::vector<int>({9, 8, 7}));
		markovChain.RegisterState(std::vector<int>({9, 8, 7}));
		markovChain.RegisterState(std::vector<int>({9, 8, 5}));
		markovChain.RegisterState(std::vector<int>({9, 8, 5}));
		markovChain.RegisterState(std::vector<int>({9, 8, 5}));
		markovChain.RegisterState(std::vector<int>({9, 8, 5}));
		markovChain.RegisterState(std::vector<int>({9, 8, 5}));

		markovChain.RegisterState(std::vector<int>({3, 5, 1}));
		markovChain.RegisterState(std::vector<int>({3, 5, 4}));
		markovChain.RegisterState(std::vector<int>({3, 5, 4}));
		markovChain.RegisterState(std::vector<int>({3, 5, 5}));
		markovChain.RegisterState(std::vector<int>({3, 5, 7}));
		markovChain.RegisterState(std::vector<int>({3, 5, 7}));
		markovChain.RegisterState(std::vector<int>({3, 5, 7}));
		markovChain.RegisterState(std::vector<int>({3, 5, 5}));
		markovChain.RegisterState(std::vector<int>({3, 5, 5}));
		markovChain.RegisterState(std::vector<int>({3, 5, 5}));
		markovChain.RegisterState(std::vector<int>({3, 5, 5}));
		markovChain.RegisterState(std::vector<int>({3, 5, 5}));

		stateRange = markovChain.GetRange(std::vector<int>({3, 5}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 4);

		stateRange = markovChain.GetRange(std::vector<int>({9, 8}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 5);

		stateRange = markovChain.GetRange(std::vector<int>({9}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 0);

		stateRange = markovChain.GetRange(std::vector<int>({3}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 0);

		stateRange = markovChain.GetRange(std::vector<int>({1}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 0);

		stateRange = markovChain.GetRange(std::vector<int>({3, 4}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 0);

		stateRange = markovChain.GetRange(std::vector<int>({3, 6}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 0);

		stateRange = markovChain.GetRange(std::vector<int>({1, 5}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 0);

		stateRange = markovChain.GetRange(std::vector<int>({3, 5, 1, 0}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 0);

		stateRange = markovChain.GetRange(std::vector<int>({3, 5, 1, 9}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 0);

		stateRange = markovChain.GetRange(std::vector<int>({9, 8, 7, 7}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 0);

		stateRange = markovChain.GetRange(std::vector<int>({4, 2, 1, 6, 8}));
		CHECK(std::distance(stateRange.m_start, stateRange.m_end), 0);
	}

	// Test MarkovChain::RegisterState
	{
		MarkovChain markovChain(3);
		MarkovState A(std::vector<int>({3, 5, 1}));
		MarkovState B(std::vector<int>({4, 2, 3}));
		MarkovState C(std::vector<int>({1, 7, 3}));
		MarkovState D(std::vector<int>({8, 3, 5}));

		markovChain.RegisterState(A);
		markovChain.RegisterState(B);
		markovChain.RegisterState(B);
		markovChain.RegisterState(A);
		markovChain.RegisterState(C);
		markovChain.RegisterState(B);
		markovChain.RegisterState(D);
		markovChain.RegisterState(D);

		CHECK(markovChain.DebugGetFrequency(A), 2);
		CHECK(markovChain.DebugGetFrequency(B), 3);
		CHECK(markovChain.DebugGetFrequency(C), 1);
		CHECK(markovChain.DebugGetFrequency(D), 2);
	}

	// Test MarkovState
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

	// Test TextSource::LoadText
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

	// Test TextSource::Split
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

	// Test TextSource::GetTokensInLine
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

	// Test TextSource::replaceAll
	{
		std::string s = "what is this ";
		TextSource::replaceAll(s, "i", "siri");
		CHECK(s, "what siris thsiris ");
	}
}

void load(MarkovChain& markovChain)
{
	FileReader fileReader;
	Dictionary dictionary;
	TextSource textSource(fileReader, dictionary);
	if (!textSource.LoadText("/home/olof/njals_saga"))
	{
		std::cerr << "load failed: " << std::endl;
		exit(1);
	}
	for (size_t idIndex = 0; idIndex < textSource.GetWordIds().size() - markovChain.GetOrder(); idIndex++)
	{
		std::vector<int> stateIds;
		for (int idOffset = 0; idOffset < markovChain.GetOrder(); idOffset++)
		{
			size_t effectiveIndex = idIndex + idOffset;
			int id = textSource.GetWordIds().at(effectiveIndex);
			stateIds.push_back(id);
		}
		MarkovState markovState(stateIds);
		markovChain.RegisterState(markovState);
	}
	std::cout << "loaded chain size: " << markovChain.GetSize() << std::endl;
}

void debugTop(MarkovChain& markovChain)
{
	int m = 0;
	std::vector<std::pair<MarkovState, int> > stateFreqs = markovChain.DebugGetStatesByFrequency();
	for (auto pStateFreq = stateFreqs.begin(); pStateFreq != stateFreqs.end(); pStateFreq++)
	{
		m++;
		if (m > 10)
		{
			break;
		}
		std::cout << "STATE:";
		pStateFreq->first.DebugToString();
		std::cout << "freq::" << pStateFreq->second << std::endl;
	}
}

int main(int argc, char* argv[])
{
	runtests();
	std::cout << "TESTS PASSED" << std::endl;

	MarkovChain markovChain(3);

	load(markovChain);

	debugTop(markovChain);


	return 0;
}
