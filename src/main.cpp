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
	std::map<MarkovState, freq_t> tmpmap;
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
		tmpmap[markovState]++;
	}
	markovChain.load_from_map(tmpmap);
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
		std::cout << pStateFreq->m_freq << "\t" << pStateFreq->m_state.DebugToString(dictionary) << std::endl;
	}
}

void ShowFirstStates(MarkovChain& markovChain, Dictionary& dictionary)
{
	std::cout << "first states:" << std::endl;
	StateFreqList_t stateFreqs = markovChain.GetFirstStates();
	for (auto pState = stateFreqs.begin(); pState != stateFreqs.end(); pState++)
	{
		std::cout << pState->m_freq << "\t" << pState->m_state.DebugToString(dictionary) << std::endl;
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
	std::string text_source_filename = params.get_string("--text", "");
	bool debug = params.get_int("--debug", 0);

	MarkovChain markovChain(0);
	Dictionary dictionary;

	if (text_source_filename.empty() == false) {
		std::cout << "Loading text source " << text_source_filename << std::endl;

		int markovOrder = params.get_int("--order", 4);
		markovChain = MarkovChain(markovOrder);
		load(markovChain, dictionary, text_source_filename);

		std::string model_output_filename = params.get_string("--save", "");

		if (model_output_filename.empty() == false) {
			// save to file
			std::ofstream fs(model_output_filename);
			if (!fs.is_open()) {
				std::cout << "could not open " << model_output_filename << std::endl;
				exit(1);
			}

			markovChain.serialize(fs);
			dictionary.serialize(fs);
			std::cout << "model saved to " << model_output_filename << std::endl;
			return 0;
		}
	}
	else {
		std::string model_input_filename = params.get_string("--load");
		std::cout << "loading model " << model_input_filename << std::endl;
		std::ifstream fs(model_input_filename);
		markovChain = MarkovChain::deserialize(fs);
		dictionary = Dictionary::deserialize(fs);
	}

	if (debug) {
		ShowTop(markovChain, dictionary);
		ShowFirstStates(markovChain, dictionary);
	}

	int count = params.get_int("--count", 10);
	std::cout << "Generating " << count << " words..." << std::endl;

	Generator generator(markovChain);
	std::vector<id_t> wordIds = generator.Generate(count, dictionary, debug);

	TextRenderer textRenderer;
	textRenderer.Render(wordIds, dictionary);

	return 0;
}
