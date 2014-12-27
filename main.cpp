#include <iostream>
#include <iterator>
#include "TextSource.h"
#include "MarkovChain.h"
#include "FileReader.h"
#include "Generator.h"
#include "UnitTests.h"

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
		std::vector<id_t> stateIds;
		for (int idOffset = 0; idOffset < markovChain.GetOrder(); idOffset++)
		{
			size_t effectiveIndex = idIndex + idOffset;
			id_t id = textSource.GetWordIds().at(effectiveIndex);
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
	std::vector<std::pair<MarkovState, freq_t> > stateFreqs = markovChain.DebugGetStatesByFrequency();
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

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		try
		{
			UnitTests::Run();
		}
		catch(const char *err)
		{
			std::string errStr(err);
			std::cout << "CAUGTH: " << errStr << std::endl;
		}
		std::cout << "TESTS PASSED" << std::endl;
		return 0;
	}

	std::string filename(argv[1]);
	Dictionary dictionary;
	MarkovChain markovChain(3);

	load(markovChain, dictionary, filename);

	//debugTop(markovChain, dictionary);

	Generator generator(markovChain);
	generator.Generate(500, dictionary);
	return 0;
}

