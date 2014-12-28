#include <iostream>
#include "Generator.h"
#include "StateRange.h"
#include "Util.h"
#include "MarkovChain.h"
#include "Dictionary.h"

Generator::Generator(MarkovChain& markovChain) :
m_markovChain(markovChain)
{
}

std::vector<id_t> Generator::Generate(unsigned count, Dictionary& dictionary)
{
	id_t periodId = dictionary.GetIdForWord(".");
	std::vector<id_t> result;

	std::vector<id_t> lastN;
	lastN.push_back(periodId);
	for (unsigned i = 0; i < count; i++)
	{
		// debug
		//std::cout << "last: " << Util::IdVecToIdAndWords(lastN, dictionary) << std::endl;

		//TODO handle if GetRange size is 0. Might happen if there is no "." in the dictionary, or some encoding problem, so dictionary.GetIdForWord(".") does not find anything.
		StateRange probabilityRange = m_markovChain.GetRange(lastN);
		freq_t totalFreq = probabilityRange.GetTotalFrequency();
		freq_t p = rand() % totalFreq;
		MarkovState state = probabilityRange.GetStateAtProbability(p);


		id_t lastRelevantId = lastN.size();
		// Normally lastRelevantId is equal to (m_markovChain.GetOrder() - 1)
		// which means that state.GetIds(lastRelevantId) should be the same as 
		// state.GetIds().back(), i.e. all ids are relevant.
		// Otherwise if lastRelevantId is smaller, then we will get the last
		// relevant part of the markov state (that should only happen in the very beginning of the text)

		id_t newWordId = state.GetIds().at(lastRelevantId);
		result.push_back(newWordId);

		lastN = GetLastN(result);

		// debug:
		//std::cout << ":"<< newWordId << std::endl;
	}
	return result;
}

std::vector<id_t> Generator::GetLastN(const std::vector<id_t>& v)
{
	unsigned N = m_markovChain.GetOrder() - 1;
	if (v.size() < N)
	{
		return v;
	}
	return std::vector<id_t>(v.end() - N, v.end());
}

Generator::~Generator()
{
}
