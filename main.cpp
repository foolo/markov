#include <iostream>
#include <queue>
#include <iterator>
#include "TextSource.h"
#include "IFileReader.h"
#include "MarkovChain.h"
#include "FileReader.h"
#include "Util.h"


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

std::string intv_to_str(std::vector<int> v)
{
	std::string s;
	for (auto it = v.begin(); it != v.end(); it++)
	{
		s = s + std::to_string(*it) + ",";
	}
	return s;
}

void runtests()
{

	// Test MarkovChain::GetRange
	{
		MarkovChain markovChain(3);
		markovChain.RegisterState(std::vector<int>({3, 5, 1}));

		StateRange stateRange = markovChain.GetRange(std::vector<int>({3, 5}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 1);

		markovChain.RegisterState(std::vector<int>({3, 6, 4}));
		markovChain.RegisterState(std::vector<int>({3, 6, 1}));
		markovChain.RegisterState(std::vector<int>({3, 6, 4}));
		markovChain.RegisterState(std::vector<int>({3, 6, 5}));

		markovChain.RegisterState(std::vector<int>({3, 9, 5}));
		markovChain.RegisterState(std::vector<int>({3, 9, 1}));

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

		// {3, 5}: 4
		// {3, 6}: 3
		// {3, 9}: 2
		// {3}: 4+3+2= 9

		stateRange = markovChain.GetRange(std::vector<int>({3}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 9);

		// {9, 8}: 5
		// {9}: 5

		stateRange = markovChain.GetRange(std::vector<int>({9}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 5);

		stateRange = markovChain.GetRange(std::vector<int>({3, 5}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 4);

		stateRange = markovChain.GetRange(std::vector<int>({9, 8}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 5);

		stateRange = markovChain.GetRange(std::vector<int>({1}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 0);

		stateRange = markovChain.GetRange(std::vector<int>({3, 4}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 0);

		stateRange = markovChain.GetRange(std::vector<int>({3, 6}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 3);

		stateRange = markovChain.GetRange(std::vector<int>({1, 5}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 0);

		stateRange = markovChain.GetRange(std::vector<int>({3, 5, 1, 0}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 0);

		stateRange = markovChain.GetRange(std::vector<int>({3, 5, 1, 9}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 0);

		stateRange = markovChain.GetRange(std::vector<int>({9, 8, 7, 7}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 0);

		stateRange = markovChain.GetRange(std::vector<int>({4, 2, 1, 6, 8}));
		CHECK(std::distance(stateRange.m_stateFreqStart, stateRange.m_stateFreqEnd), 0);
	}

	// Test StateRange::GetTotalFrequency and GetStateAtProbability
	{
		MarkovChain markovChain(3);
		markovChain.RegisterState(std::vector<int>({3, 6, 4}));
		markovChain.RegisterState(std::vector<int>({3, 6, 1}));
		markovChain.RegisterState(std::vector<int>({3, 6, 4}));
		markovChain.RegisterState(std::vector<int>({3, 6, 5}));

		markovChain.RegisterState(std::vector<int>({3, 5, 4}));
		markovChain.RegisterState(std::vector<int>({3, 5, 1}));
		markovChain.RegisterState(std::vector<int>({3, 5, 4}));
		markovChain.RegisterState(std::vector<int>({3, 5, 5}));
		markovChain.RegisterState(std::vector<int>({3, 5, 5}));
		markovChain.RegisterState(std::vector<int>({3, 5, 1}));

		StateRange stateRange = markovChain.GetRange(std::vector<int>({3, 5}));
		CHECK(stateRange.GetTotalFrequency(), 6);

		stateRange = markovChain.GetRange(std::vector<int>({3, 6}));
		CHECK(stateRange.GetTotalFrequency(), 4);

		stateRange = markovChain.GetRange(std::vector<int>({3}));
		CHECK(stateRange.GetTotalFrequency(), 10);

		CHECK(intv_to_str(stateRange.GetStateAtProbability(0).GetIds()), "3,5,1,");
		CHECK(intv_to_str(stateRange.GetStateAtProbability(1).GetIds()), "3,5,1,");
		CHECK(intv_to_str(stateRange.GetStateAtProbability(2).GetIds()), "3,5,4,");
		CHECK(intv_to_str(stateRange.GetStateAtProbability(3).GetIds()), "3,5,4,");
		CHECK(intv_to_str(stateRange.GetStateAtProbability(4).GetIds()), "3,5,5,");
		CHECK(intv_to_str(stateRange.GetStateAtProbability(5).GetIds()), "3,5,5,");
		CHECK(intv_to_str(stateRange.GetStateAtProbability(6).GetIds()), "3,6,1,");
		CHECK(intv_to_str(stateRange.GetStateAtProbability(7).GetIds()), "3,6,4,");
		CHECK(intv_to_str(stateRange.GetStateAtProbability(8).GetIds()), "3,6,4,");
		CHECK(intv_to_str(stateRange.GetStateAtProbability(9).GetIds()), "3,6,5,");
		
		std::string errStr;
		try
		{
			stateRange.GetStateAtProbability(10);
		}
		catch (char const* err)
		{
			errStr = std::string(err);
		}
		CHECK (errStr, "Out of range")
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

	// Test MarkovChain::GetAccumulatedFrequencies
	{
		MarkovChain markovChain(3);

		markovChain.RegisterState(std::vector<int>({3, 6, 4}));
		markovChain.RegisterState(std::vector<int>({3, 6, 1}));
		markovChain.RegisterState(std::vector<int>({3, 6, 4}));
		markovChain.RegisterState(std::vector<int>({3, 6, 5}));

		markovChain.RegisterState(std::vector<int>({3, 9, 5}));
		markovChain.RegisterState(std::vector<int>({3, 9, 1}));

		markovChain.RegisterState(std::vector<int>({3, 5, 4}));
		markovChain.RegisterState(std::vector<int>({3, 5, 1}));
		markovChain.RegisterState(std::vector<int>({3, 5, 4}));
		markovChain.RegisterState(std::vector<int>({3, 5, 4}));
		markovChain.RegisterState(std::vector<int>({3, 5, 5}));
		markovChain.RegisterState(std::vector<int>({3, 5, 1}));

		std::vector<unsigned> accFreqs = markovChain.GetAccumulatedFrequencies();
		CHECK(accFreqs.size(), 8);
		int i = 0;
		CHECK(accFreqs.at(i++), 2); // 3 5 1	/ 2		/ 2
		CHECK(accFreqs.at(i++), 5); // 3 5 4	/ 3		/ 5
		CHECK(accFreqs.at(i++), 6); // 3 5 5	/ 1		/ 6
		CHECK(accFreqs.at(i++), 7); // 3 6 1	/ 1		/ 7
		CHECK(accFreqs.at(i++), 9); // 3 6 4	/ 2		/ 9
		CHECK(accFreqs.at(i++), 10); // 3 6 5	/ 1		/ 10
		CHECK(accFreqs.at(i++), 11); // 3 9 1	/ 1		/ 11
		CHECK(accFreqs.at(i++), 12); // 3 9 5	/ 1		/ 12
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

void load(MarkovChain& markovChain, Dictionary& dictionary, const std::string& filename)
{
	FileReader fileReader;
	TextSource textSource(fileReader, dictionary);
	if (!textSource.LoadText(filename))
	{
		std::cerr << "load failed: " << filename << std::endl;
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

void debugTop(MarkovChain& markovChain, Dictionary& dictionary)
{
	int m = 0;
	std::vector<std::pair<MarkovState, int> > stateFreqs = markovChain.DebugGetStatesByFrequency();
	for (auto pStateFreq = stateFreqs.begin(); pStateFreq != stateFreqs.end(); pStateFreq++)
	{
		m++;
		if (m > 30)
		{
			break;
		}
		std::cout << "STATE:";
		std::cout << pStateFreq->first.DebugToString(dictionary) << std::endl;
		std::cout << "freq::" << pStateFreq->second << std::endl;
	}
}

//TODO Convert int to unsigned where applicable

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		runtests();
		std::cout << "TESTS PASSED" << std::endl;
		return 0;
	}

	std::string filename(argv[1]);
	Dictionary dictionary;
	MarkovChain markovChain(3);

	load(markovChain, dictionary, filename);

	debugTop(markovChain, dictionary);


	return 0;
}
