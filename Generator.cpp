#include <iostream>
#include "Generator.h"
#include "Util.h"

Generator::Generator(MarkovChain& markovChain) :
m_markovChain(markovChain)
{
}

std::vector<int> Generator::Generate(unsigned count, Dictionary& dictionary)
{
	std::string resultStr;
	std::vector<unsigned> accFreq = m_markovChain.GetAccumulatedFrequencies();
	int periodId = dictionary.GetIdForWord(".");
	std::vector<int> result;
	result.push_back(periodId);
	
	std::cout << "Starting generator" << std::endl;
	
	for(unsigned i = 0; i < count; i++)
	{
		std::vector<int> lastN = GetLastN(result);
		
		// debug
		//std::cout << "last: " << Util::IntVecToIdAndWords(lastN, dictionary) << std::endl;
		
		StateRange probabilityRange = m_markovChain.GetRange(lastN);
		int totalFreq = probabilityRange.GetTotalFrequency();
		int p = rand() % totalFreq;
		MarkovState state = probabilityRange.GetStateAtProbability(p);
		
		
		int lastRelevantId = lastN.size(); 
		// Normally lastRelevantId is equal to (m_markovChain.GetOrder() - 1)
		// which means that state.GetIds(lastRelevantId) should be the same as 
		// state.GetIds().back(), i.e. all ids are relevant.
		// Otherwise if lastRelevantId is smaller, then we will get the last
		// relevant part of the markov state (that should only happen in the very beginning of the text)
			
		int newWordId = state.GetIds().at(lastRelevantId);
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

std::vector<int> Generator::GetLastN(const std::vector<int>& v)
{
	unsigned N = m_markovChain.GetOrder() - 1;
	if(v.size() < N)
	{
		return v;
	}
	return std::vector<int>(v.end() - N, v.end());
}

Generator::~Generator()
{
}

