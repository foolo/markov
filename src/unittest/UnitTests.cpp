#include "UnitTests.h"
#include "MarkovChain.h"
#include "Util.h"
#include "TextBank.h"
#include "StateRange.h"
#include "Dictionary.h"
#include "FileReader.h"

void UnitTests::Run()
{
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

	// Test TextBank::LoadText
	{
		Dictionary dictionary;
		FileReaderMock mockFileReader;
		TextBank textSource(mockFileReader, dictionary);
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

	// Test FileReader::GetTokensInLine
	{
		std::vector<std::string> result = FileReader::GetTokensInLine("%&/test [ split a« +string.that, is amazing");
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

	// Test FileReader::replaceAll
	{
		std::string s = "what is this ";
		FileReader::replaceAll(s, "i", "siri");
		CHECK(s, "what siris thsiris ");
	}

}
