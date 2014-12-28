#include "UnitTests.h"
#include "MarkovChain.h"
#include "Util.h"
#include "TextSource.h"
#include "StateRange.h"
#include "Dictionary.h"

void UnitTests::Run()
{
	// Test MarkovChain::GetRange
	{
		MarkovChain markovChain(3);
		markovChain.RegisterState(std::vector<id_t>({3, 5, 1}));

		StateRange stateRange = markovChain.GetRange(std::vector<id_t>({3, 5}));
		CHECK(stateRange.Size(), 1);

		markovChain.RegisterState(std::vector<id_t>({3, 6, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 6, 1}));
		markovChain.RegisterState(std::vector<id_t>({3, 6, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 6, 5}));

		markovChain.RegisterState(std::vector<id_t>({3, 9, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 9, 1}));

		markovChain.RegisterState(std::vector<id_t>({3, 5, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 1}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 1}));

		markovChain.RegisterState(std::vector<id_t>({9, 8, 4}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 1}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 4}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 5}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 5}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 9}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 9}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 9}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 1}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 1}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 4}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 4}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 5}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 7}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 7}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 7}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 5}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 5}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 5}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 5}));
		markovChain.RegisterState(std::vector<id_t>({9, 8, 5}));

		markovChain.RegisterState(std::vector<id_t>({3, 5, 1}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 7}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 7}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 7}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 5}));

		// {3, 5}: 4
		// {3, 6}: 3
		// {3, 9}: 2
		// {3}: 4+3+2= 9

		stateRange = markovChain.GetRange(std::vector<id_t>({3}));
		CHECK(stateRange.Size(), 9);

		// {9, 8}: 5
		// {9}: 5

		stateRange = markovChain.GetRange(std::vector<id_t>({9}));
		CHECK(stateRange.Size(), 5);

		stateRange = markovChain.GetRange(std::vector<id_t>({3, 5}));
		CHECK(stateRange.Size(), 4);

		stateRange = markovChain.GetRange(std::vector<id_t>({9, 8}));
		CHECK(stateRange.Size(), 5);


		std::string errStr;
		try
		{
			stateRange = markovChain.GetRange(std::vector<id_t>({1}));
		}
		catch (char const* err)
		{
			errStr = std::string(err);
		}
		CHECK(errStr, "Empty range")


		errStr.clear();
		try
		{
			stateRange = markovChain.GetRange(std::vector<id_t>({3, 4}));
		}
		catch (char const* err)
		{
			errStr = std::string(err);
		}
		CHECK(errStr, "Empty range")


		stateRange = markovChain.GetRange(std::vector<id_t>({3, 6}));
		CHECK(stateRange.Size(), 3);

		errStr.clear();
		try
		{
			stateRange = markovChain.GetRange(std::vector<id_t>({1, 5}));
		}
		catch (char const* err)
		{
			errStr = std::string(err);
		}
		CHECK(errStr, "Empty range")

		errStr.clear();
		try
		{
			stateRange = markovChain.GetRange(std::vector<id_t>({3, 5, 1, 0}));
		}
		catch (char const* err)
		{
			errStr = std::string(err);
		}
		CHECK(errStr, "Empty range")

		errStr.clear();
		try
		{
			stateRange = markovChain.GetRange(std::vector<id_t>({3, 5, 1, 9}));
		}
		catch (char const* err)
		{
			errStr = std::string(err);
		}
		CHECK(errStr, "Empty range")

		errStr.clear();
		try
		{
			stateRange = markovChain.GetRange(std::vector<id_t>({9, 8, 7, 7}));
		}
		catch (char const* err)
		{
			errStr = std::string(err);
		}
		CHECK(errStr, "Empty range")

		errStr.clear();
		try
		{
			stateRange = markovChain.GetRange(std::vector<id_t>({4, 2, 1, 6, 8}));
		}
		catch (char const* err)
		{
			errStr = std::string(err);
		}
		CHECK(errStr, "Empty range")
	}

	// Test StateRange::GetTotalFrequency and GetStateAtProbability
	{
		MarkovChain markovChain(3);
		markovChain.RegisterState(std::vector<id_t>({3, 6, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 6, 1}));
		markovChain.RegisterState(std::vector<id_t>({3, 6, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 6, 5}));

		markovChain.RegisterState(std::vector<id_t>({3, 5, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 1}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 1}));

		StateRange stateRange = markovChain.GetRange(std::vector<id_t>({3, 5}));
		CHECK(stateRange.GetTotalFrequency(), 6);

		stateRange = markovChain.GetRange(std::vector<id_t>({3, 6}));
		CHECK(stateRange.GetTotalFrequency(), 4);

		stateRange = markovChain.GetRange(std::vector<id_t>({3}));
		CHECK(stateRange.GetTotalFrequency(), 10);

		CHECK(Util::IdVecToStr(stateRange.GetStateAtProbability(0).GetIds()), "3,5,1,");
		CHECK(Util::IdVecToStr(stateRange.GetStateAtProbability(1).GetIds()), "3,5,1,");
		CHECK(Util::IdVecToStr(stateRange.GetStateAtProbability(2).GetIds()), "3,5,4,");
		CHECK(Util::IdVecToStr(stateRange.GetStateAtProbability(3).GetIds()), "3,5,4,");
		CHECK(Util::IdVecToStr(stateRange.GetStateAtProbability(4).GetIds()), "3,5,5,");
		CHECK(Util::IdVecToStr(stateRange.GetStateAtProbability(5).GetIds()), "3,5,5,");
		CHECK(Util::IdVecToStr(stateRange.GetStateAtProbability(6).GetIds()), "3,6,1,");
		CHECK(Util::IdVecToStr(stateRange.GetStateAtProbability(7).GetIds()), "3,6,4,");
		CHECK(Util::IdVecToStr(stateRange.GetStateAtProbability(8).GetIds()), "3,6,4,");
		CHECK(Util::IdVecToStr(stateRange.GetStateAtProbability(9).GetIds()), "3,6,5,");

		std::string errStr;
		try
		{
			stateRange.GetStateAtProbability(10);
		}
		catch (char const* err)
		{
			errStr = std::string(err);
		}
		CHECK(errStr, "Out of range")
	}

	// Test MarkovChain::RegisterState
	{
		MarkovChain markovChain(3);
		MarkovState A(std::vector<id_t>({3, 5, 1}));
		MarkovState B(std::vector<id_t>({4, 2, 3}));
		MarkovState C(std::vector<id_t>({1, 7, 3}));
		MarkovState D(std::vector<id_t>({8, 3, 5}));

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

		markovChain.RegisterState(std::vector<id_t>({3, 6, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 6, 1}));
		markovChain.RegisterState(std::vector<id_t>({3, 6, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 6, 5}));

		markovChain.RegisterState(std::vector<id_t>({3, 9, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 9, 1}));

		markovChain.RegisterState(std::vector<id_t>({3, 5, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 1}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 4}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 5}));
		markovChain.RegisterState(std::vector<id_t>({3, 5, 1}));

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
		CHECK(MarkovState(std::vector<id_t>({1, 2, 3})) < MarkovState(std::vector<id_t>({1, 2, 4})), true)
		CHECK(MarkovState(std::vector<id_t>({5, 6})) < MarkovState(std::vector<id_t>({3, 2, 1})), true)
		CHECK(MarkovState(std::vector<id_t>({5})) < MarkovState(std::vector<id_t>({1, 2, 3})), true)
		CHECK(MarkovState(std::vector<id_t>({1, 2, 3})) < MarkovState(std::vector<id_t>({1, 2, 3, 1})), true)

		CHECK(MarkovState(std::vector<id_t>({1, 2, 4})) < MarkovState(std::vector<id_t>({1, 2, 3})), false)
		CHECK(MarkovState(std::vector<id_t>({3, 2, 1})) < MarkovState(std::vector<id_t>({5, 6})), false)
		CHECK(MarkovState(std::vector<id_t>({1, 2, 3})) < MarkovState(std::vector<id_t>({5})), false)
		CHECK(MarkovState(std::vector<id_t>({1, 2, 3, 1})) < MarkovState(std::vector<id_t>({1, 2, 3})), false)

		CHECK(MarkovState(std::vector<id_t>({4, 2, 7})) < MarkovState(std::vector<id_t>({4, 2, 7})), false)

		CHECK(MarkovState(std::vector<id_t>({5})) < MarkovState(std::vector<id_t>({5})), false)
		CHECK(MarkovState(std::vector<id_t>({})) < MarkovState(std::vector<id_t>({})), false)

		CHECK(MarkovState(std::vector<id_t>({8, 2, 3})) < MarkovState(std::vector<id_t>({9, 2, 3})), true)
		CHECK(MarkovState(std::vector<id_t>({8, 2, 4})) < MarkovState(std::vector<id_t>({8, 3, 3})), true)
		CHECK(MarkovState(std::vector<id_t>({9, 2, 3})) < MarkovState(std::vector<id_t>({8, 2, 3})), false)
		CHECK(MarkovState(std::vector<id_t>({8, 3, 3})) < MarkovState(std::vector<id_t>({8, 2, 4})), false)
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
