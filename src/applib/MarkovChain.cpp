#include <algorithm>
#include <fstream>
#include <iostream>
#include "MarkovChain.h"
#include "StateRange.h"
#include "util/SerializeUtils.h"
#include "util/Timer.h"

MarkovChain::MarkovChain(int markovOrder) :
m_markovOrder(markovOrder)
{
}

StateFreqList_t MarkovChain::GetStatesByFrequency()
{
	StateFreqList_t pairs;
	for (auto itr = m_stateFrequencies.begin(); itr != m_stateFrequencies.end(); ++itr)
	{
		pairs.push_back(*itr);
	}

	std::sort(pairs.begin(), pairs.end(), [ = ](const StateFreq& a, const StateFreq& b){
		return a.m_freq > b.m_freq;
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

	std::vector<StateFreq>::iterator start = std::lower_bound(m_stateFrequencies.begin(), m_stateFrequencies.end(), lowerState);
	std::vector<StateFreq>::iterator end = std::lower_bound(m_stateFrequencies.begin(), m_stateFrequencies.end(), upperState);

	if (start == end)
	{
		std::cout << "Empty range" << std::endl;
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
		accFreq += pStateFreq->m_freq;
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
		itr->serialize(s);
		i++;
	}
	std::cout << "serialized " << i << " states" << std::endl;
}

MarkovChain MarkovChain::deserialize(std::istream& s) {
	Timer timer;
	SerializeUtils::assert(s, "states");
	unsigned size = SerializeUtils::read_unsigned(s);
	SerializeUtils::assert(s, "order");
	unsigned order = SerializeUtils::read_unsigned(s);
	MarkovChain markovChain(order);
	std::cout << "deserializing size " << size << std::endl;
	std::cout << "deserializing order " << order << std::endl;
	for (size_t i = 0; i < size; i++) {
		StateFreq state;
		state.deserialize(s, order);
		markovChain.m_stateFrequencies.push_back(state);
	}
	std::cout << "deserialized size " << markovChain.m_stateFrequencies.size() << std::endl;
	std::cout << "deserialize time: " << timer.get_elapsed_time() << std::endl;
	return markovChain;
}

void MarkovChain::load_from_map(std::map<MarkovState, freq_t>& map) {
	std::map<MarkovState, freq_t>::iterator state = map.begin();
	for (state = map.begin(); state != map.end(); ++state) {
		m_stateFrequencies.push_back(StateFreq(state->first, state->second));
	}
}

MarkovChain::~MarkovChain()
{
}
