#include "StateRange.h"

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
