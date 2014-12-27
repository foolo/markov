#include <map>
#include <algorithm>
#include <limits.h>
#include <sstream>
#include <iostream>
#include "MarkovChain.h"
#include "StateRange.h"
#include "Util.h"

MarkovChain::MarkovChain(int markovOrder) :
m_markovOrder(markovOrder)
{
}

void MarkovChain::RegisterState(const MarkovState& state)
{
	m_stateFrequencies[state]++;
}

freq_t MarkovChain::DebugGetFrequency(const MarkovState& state)
{
	return m_stateFrequencies[state];
}

std::vector<std::pair<MarkovState, freq_t> > MarkovChain::DebugGetStatesByFrequency()
{
	std::vector<std::pair<MarkovState, freq_t>> pairs;  //TODO convert to type
	for (auto itr = m_stateFrequencies.begin(); itr != m_stateFrequencies.end(); ++itr)
		pairs.push_back(*itr);

	std::sort(pairs.begin(), pairs.end(), [ = ](const std::pair<MarkovState, freq_t>& a, const std::pair<MarkovState, freq_t>& b){
		return a.second > b.second;
	});
	return pairs;
}

void MarkovChain::ZeroPad(std::vector<id_t>& firstWords)
{
	while (firstWords.size() < m_markovOrder)
	{
		firstWords.push_back(0);
	}
}

StateRange MarkovChain::GetRange(std::vector<id_t> firstWords)
{
	// for example  if firstWords == {7, 5, 2}
	//
	// firstWordsLower = {7, 5, 2, 0}
	// firstWordsUpper = {7, 5, 3, 0}   // (note the 3)

	std::vector<id_t> firstWordsLower(firstWords);
	std::vector<id_t> firstWordsUpper(firstWords);
	firstWordsUpper.back()++;

	ZeroPad(firstWordsLower);
	ZeroPad(firstWordsUpper);

	MarkovState lowerState(firstWordsLower);
	MarkovState upperState(firstWordsUpper);

	StateFreqMap_t::iterator start(m_stateFrequencies.lower_bound(lowerState));
	StateFreqMap_t::iterator end(m_stateFrequencies.upper_bound(upperState));
	
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

