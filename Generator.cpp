#include <iostream>
#include "Generator.h"
#include "Util.h"

Generator::Generator(MarkovChain& markovChain) :
m_markovChain(markovChain)
{
}

std::vector<id_t> Generator::Generate(unsigned count, Dictionary& dictionary)
{
	std::string resultStr;
	std::vector<unsigned> accFreq = m_markovChain.GetAccumulatedFrequencies();
	id_t periodId = dictionary.GetIdForWord(".");
	std::vector<id_t> result;
	result.push_back(periodId);
	
	std::cout << "Starting generator" << std::endl;
	
	for(unsigned i = 0; i < count; i++)
	{
		std::vector<id_t> lastN = GetLastN(result);
		
		// debug
		//std::cout << "last: " << Util::IdVecToIdAndWords(lastN, dictionary) << std::endl;
		
		//TODO handle if GetRange size is 0
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
		std::string newWord = dictionary.SearchWordForId(newWordId);
		
		
		resultStr += newWord + " ";
		
		if (newWord == ".")
		{
			resultStr += "\n";
		}

		// debug:
		//std::cout << ":"<< newWord << std::endl;
	}
	
	std::cout << "RESULT:" << std::endl << resultStr << std::endl;
	return result;
}

std::vector<id_t> Generator::GetLastN(const std::vector<id_t>& v)
{
	unsigned N = m_markovChain.GetOrder() - 1;
	if(v.size() < N)
	{
		return v;
	}
	return std::vector<id_t>(v.end() - N, v.end());
}

Generator::~Generator()
{
}

