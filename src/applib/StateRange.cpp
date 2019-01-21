#include <iostream>
#include "StateRange.h"
#include "Dictionary.h"

StateRange::StateRange(StateFreqMap_t::iterator start, StateFreqMap_t::iterator end) :
m_stateFreqStart(start), m_stateFreqEnd(end)
{
}

freq_t StateRange::GetTotalFrequency()
{
	freq_t sum = 0;
	for (auto pStateFreq = m_stateFreqStart; pStateFreq != m_stateFreqEnd; pStateFreq++)
	{
		sum += pStateFreq->second;
	}
	return sum;
}

MarkovState StateRange::GetStateAtProbability(freq_t p)
{
	freq_t sum = 0;
	for (auto pStateFreq = m_stateFreqStart; pStateFreq != m_stateFreqEnd; pStateFreq++)
	{
		sum += pStateFreq->second;
		if (sum > p)
		{
			return pStateFreq->first;
		}
	}
	throw "Out of range";
}

StateFreqMap_t::difference_type StateRange::Size()
{
	return std::distance(m_stateFreqStart, m_stateFreqEnd);
}

void StateRange::print(Dictionary& dictionary, id_t lastRelevantId)
{
	long i = 0;
	auto pStateFreq = m_stateFreqStart;
	for (; pStateFreq != m_stateFreqEnd; pStateFreq++)
	{
		i++;
		if (i < 10) {
			const MarkovState &markovState(pStateFreq->first);
			freq_t freq = pStateFreq->second;
			id_t id = markovState.GetIds().at(lastRelevantId);
			std::string word = dictionary.SearchWordForId(id);
			std::cout << " - " << freq << "\t" << word << std::endl;
		}
		else {
			break;
		}
	}
	auto states_left = std::distance(pStateFreq, m_stateFreqEnd);
	if (states_left > 0) {
		std::cout << " - " << "and " << states_left << " more" << std::endl;
	}
}
