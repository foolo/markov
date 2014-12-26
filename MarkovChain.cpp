#include <map>
#include <algorithm>
#include <limits.h>
#include <sstream>
#include <iostream>
#include "MarkovChain.h"
#include "Util.h"

//TODO Excract StateRange to own file

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

MarkovChain::MarkovChain(int markovOrder) :
m_markovOrder(markovOrder)
{
}

void MarkovChain::RegisterState(const MarkovState& state)
{
	m_stateFrequencies[state]++;
}

int MarkovChain::DebugGetFrequency(const MarkovState& state)
{
	return m_stateFrequencies[state];
}

std::vector<std::pair<MarkovState, int> > MarkovChain::DebugGetStatesByFrequency()
{
	std::vector<std::pair<MarkovState, int>> pairs;
	for (auto itr = m_stateFrequencies.begin(); itr != m_stateFrequencies.end(); ++itr)
		pairs.push_back(*itr);

	std::sort(pairs.begin(), pairs.end(), [ = ](const std::pair<MarkovState, int>& a, const std::pair<MarkovState, int>& b){
		return a.second > b.second;
	});
	return pairs;
}

void MarkovChain::ZeroPad(std::vector<int>& firstWords)
{
	while (firstWords.size() < m_markovOrder)
	{
		firstWords.push_back(0);
	}
}

StateRange MarkovChain::GetRange(std::vector<int> firstWords)
{
	// for example  if firstWords == {7, 5, 2}
	//
	// firstWordsLower = {7, 5, 2, 0}
	// firstWordsUpper = {7, 5, 3, 0}   // (note the 3)

	std::vector<int> firstWordsLower(firstWords);
	std::vector<int> firstWordsUpper(firstWords);
	firstWordsUpper.back()++;

	ZeroPad(firstWordsLower);
	ZeroPad(firstWordsUpper);

	MarkovState lowerState(firstWordsLower);
	MarkovState upperState(firstWordsUpper);

	std::map<MarkovState, int>::iterator start(m_stateFrequencies.lower_bound(lowerState));
	std::map<MarkovState, int>::iterator end(m_stateFrequencies.upper_bound(upperState));
	
	if (start == end)
	{
		throw "Empty range";
	}
	
	return StateRange(start, end);
}

int MarkovChain::GetOrder()
{
	return m_markovOrder;
}

size_t MarkovChain::GetSize()
{
	return m_stateFrequencies.size();
}

std::vector<unsigned> MarkovChain::GetAccumulatedFrequencies()
{
	std::vector<unsigned> accFreqs;
	unsigned accFreq = 0;
	for (auto pStateFreq = m_stateFrequencies.begin(); pStateFreq != m_stateFrequencies.end(); pStateFreq++)
	{
		accFreq += pStateFreq->second;
		accFreqs.push_back(accFreq);
	}
	return accFreqs;
}

MarkovChain::~MarkovChain()
{
}

