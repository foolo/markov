#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include "TextSource.h"
#include "MarkovChain.h"
#include "FileReader.h"
#include "Generator.h"
#include "Dictionary.h"
#include "TextRenderer.h"

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

void parseParameters(int argc, char* argv[], std::string& filename, int& count)
{
	std::vector<std::string> args;
	for (int i = 0; i < argc; i++)
	{
		args.push_back(argv[i]);
	}
	if (argc < 3)
	{
		std::cout << "Usage: " << argv[0] << " <filename> <number of words to generate>" << std::endl;
		exit(1);
	}
	std::istringstream(args.at(1)) >> filename;
	std::istringstream(args.at(2)) >> count;
}

int main(int argc, char* argv[])
{
	initLocale(LC_ALL, "en_US.utf8");

	std::string filename;
	int count;
	parseParameters(argc, argv, filename, count);

	std::cout << "Loading " << filename << std::endl;

	Dictionary dictionary;
	MarkovChain markovChain(3);
	load(markovChain, dictionary, filename);

	ShowTop(markovChain, dictionary);

	std::cout << "Generating " << count << " words..." << std::endl;

	Generator generator(markovChain);
	std::vector<id_t> wordIds = generator.Generate(count, dictionary);

	TextRenderer textRenderer;
	textRenderer.Render(wordIds, dictionary);
	return 0;
}