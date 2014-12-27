#include "StateRange.h"

StateRange::StateRange(std::map<MarkovState, int>::iterator start, std::map<MarkovState, int>::iterator end) :
m_stateFreqStart(start), m_stateFreqEnd(end)
{
}

int StateRange::GetTotalFrequency()
{
	int sum = 0;
	for (auto pStateFreq = m_stateFreqStart; pStateFreq != m_stateFreqEnd; pStateFreq++)
	{
		sum += pStateFreq->second;
	}
	return sum;
}

MarkovState StateRange::GetStateAtProbability(int p)
{
	int sum = 0;
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
