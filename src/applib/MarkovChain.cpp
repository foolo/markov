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

StateFreqList_t MarkovChain::GetStatesByFrequency()
{
	StateFreqList_t pairs;
	for (auto itr = m_stateFrequencies.begin(); itr != m_stateFrequencies.end(); ++itr)
	{
		pairs.push_back(*itr);
	}

	std::sort(pairs.begin(), pairs.end(), [ = ](const MarkovStateFreq& a, const MarkovStateFreq& b){
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

	StateFreqMap_t::iterator start = std::lower_bound(m_stateFrequencies.begin(), m_stateFrequencies.end(), lowerState);
	StateFreqMap_t::iterator end = std::lower_bound(m_stateFrequencies.begin(), m_stateFrequencies.end(), upperState);

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
		const MarkovState &state = itr->m_state;
		freq_t freq = itr->m_freq;
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
		markovChain.m_stateFrequencies.push_back(MarkovStateFreq(state, freq));
	}
	std::cout << "deserialized size " << markovChain.m_stateFrequencies.size() << std::endl;
	return markovChain;
}

void MarkovChain::load_from_map(std::map<MarkovState, freq_t>& map) {
	std::map<MarkovState, freq_t>::iterator state = map.begin();
	for (state = map.begin(); state != map.end(); ++state) {
		m_stateFrequencies.push_back(MarkovStateFreq(state->first, state->second));
	}
}

MarkovChain::~MarkovChain()
{
}
