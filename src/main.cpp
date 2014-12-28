#include <iostream>
#include <iterator>
#include "TextSource.h"
#include "MarkovChain.h"
#include "FileReader.h"
#include "Generator.h"
#include "UnitTests.h"
#include "Dictionary.h"

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

void ShowTop(MarkovChain& markovChain, Dictionary& dictionary)
{
	int m = 0;
	StateFreqList_t stateFreqs = markovChain.GetStatesByFrequency();
	for (auto pStateFreq = stateFreqs.begin(); pStateFreq != stateFreqs.end(); pStateFreq++)
	{
		m++;
		if (m > 30)
		{
			break;
		}
		std::cout << pStateFreq->second << "\t" << pStateFreq->first.DebugToString(dictionary) << std::endl;
	}
}

void initLocale(int category, const std::string& locStr)
{
	char* res = setlocale(category, locStr.c_str());
	if (res == NULL)
	{
		std::cerr << "setlocale " << category << " failed: " << locStr << std::endl;
		exit(1);
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
		catch (const char *err)
		{
			std::string errStr(err);
			std::cout << "CAUGTH: " << errStr << std::endl;
		}
		std::cout << "TESTS PASSED" << std::endl;
		return 0;
	}

	initLocale(LC_ALL, "en_US.utf8");

	std::string filename(argv[1]);
	Dictionary dictionary;
	MarkovChain markovChain(3);

	load(markovChain, dictionary, filename);

	ShowTop(markovChain, dictionary);

	Generator generator(markovChain);
	generator.Generate(500, dictionary);
	return 0;
}
