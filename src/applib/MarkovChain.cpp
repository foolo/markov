#include <algorithm>
#include <fstream>
#include <iostream>
#include "MarkovChain.h"
#include "StateRange.h"
#include "util/SerializeUtils.h"

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

StateFreqList_t MarkovChain::GetStatesByFrequency()
{
	StateFreqList_t pairs;
	for (auto itr = m_stateFrequencies.begin(); itr != m_stateFrequencies.end(); ++itr)
	{
		pairs.push_back(*itr);
	}

	std::sort(pairs.begin(), pairs.end(), [ = ](const std::pair<MarkovState, freq_t>& a, const std::pair<MarkovState, freq_t>& b){
		return a.second > b.second;
	});
	return pairs;
}

StateFreqList_t MarkovChain::GetFirstStates()
{
	int i = 0;
	StateFreqList_t pairs;
	for (auto itr = m_stateFrequencies.begin(); itr != m_stateFrequencies.end(); ++itr)
	{
		pairs.push_back(*itr);
		if (i++ > 30) {
			break;
		}
	}
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
	if (firstWords.empty())
	{
		return StateRange(m_stateFrequencies.begin(), m_stateFrequencies.end());
	}

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

void MarkovChain::serialize(std::ostream &s)
{
	s << "states ";
	s << m_stateFrequencies.size() << std::endl;
	s << "order ";
	s << m_markovOrder << std::endl;
	std::cout << "serializing " << m_stateFrequencies.size() << " states" << std::endl;
	long i = 0;
	for (auto itr = m_stateFrequencies.begin(); itr != m_stateFrequencies.end(); ++itr) {
		const MarkovState &state = itr->first;
		freq_t freq = itr->second;
		state.serialize(s);
		s << "freq " << freq << std::endl;
		i++;
	}
	std::cout << "serialized " << i << " states" << std::endl;
}

MarkovChain MarkovChain::deserialize(std::istream& s) {
	SerializeUtils::assert(s, "states");
	unsigned size = SerializeUtils::read_unsigned(s);
	SerializeUtils::assert(s, "order");
	unsigned order = SerializeUtils::read_unsigned(s);
	MarkovChain markovChain(order);
	std::cout << "deserializing size " << size << std::endl;
	std::cout << "deserializing order " << order << std::endl;
	std::vector<std::pair<MarkovState, freq_t> > foo;
	for (size_t i = 0; i < size; i++) {
		MarkovState state;
		state.deserialize(s, order);
		SerializeUtils::assert(s, "freq");
		freq_t freq = SerializeUtils::read_unsigned_long(s);
		markovChain.m_stateFrequencies[state] = freq;
	}
	std::cout << "deserialized size " << markovChain.m_stateFrequencies.size() << std::endl;
	return markovChain;
}

MarkovChain::~MarkovChain()
{
}
