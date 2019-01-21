#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include "TextBank.h"
#include "MarkovChain.h"
#include "FileReader.h"
#include "Generator.h"
#include "Dictionary.h"
#include "TextRenderer.h"
#include "util/ParameterParser.h"

void load(MarkovChain& markovChain, Dictionary& dictionary, const std::string& filename)
{
	FileReader fileReader;
	TextBank textSource(fileReader, dictionary);
	if (!textSource.LoadText(filename))
	{
		std::cerr << "load failed: " << filename << std::endl;
		exit(1);
	}
	std::cout << "Building Markov chain of order " << markovChain.GetOrder() << "..." << std::endl;
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
	std::cout << "states by frequency:" << std::endl;
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

void ShowFirstStates(MarkovChain& markovChain, Dictionary& dictionary)
{
	std::cout << "first states:" << std::endl;
	StateFreqList_t stateFreqs = markovChain.GetFirstStates();
	for (auto pState = stateFreqs.begin(); pState != stateFreqs.end(); pState++)
	{
		std::cout << pState->second << "\t" << pState->first.DebugToString(dictionary) << std::endl;
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
	initLocale(LC_ALL, "en_US.utf8");

	ParameterParser params(argc, argv);
	std::string filename = params.get_string("--text");
	int count = params.get_int("--count", 10);
	int markovOrder = params.get_int("--order", 4);
	bool debug = params.get_int("--debug", 0);

	std::cout << "Loading " << filename << std::endl;

	Dictionary dictionary;
	MarkovChain markovChain(markovOrder);
	load(markovChain, dictionary, filename);

	if (debug) {
		ShowTop(markovChain, dictionary);
		ShowFirstStates(markovChain, dictionary);
	}

	std::cout << "Generating " << count << " words..." << std::endl;

	Generator generator(markovChain);
	std::vector<id_t> wordIds = generator.Generate(count, dictionary, debug);

	TextRenderer textRenderer;
	textRenderer.Render(wordIds, dictionary);
	return 0;
}
