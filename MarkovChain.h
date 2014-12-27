#ifndef MARKOVCHAIN_H
#define	MARKOVCHAIN_H

#include <vector>
#include "Dictionary.h"
#include "MarkovState.h"
#include "StateRange.h"

class StateRange;

class MarkovChain
{
private:
	StateFreqMap_t m_stateFrequencies;
	unsigned m_markovOrder;

public:
	MarkovChain(int markovOrder);
	void RegisterState(const MarkovState& state);
	freq_t DebugGetFrequency(const MarkovState& state);
	std::vector<std::pair<MarkovState, freq_t>> DebugGetStatesByFrequency(); // TODO remove debug fuctions
	void ZeroPad(std::vector<id_t>& firstWords);
	StateRange GetRange(std::vector<id_t> firstWords);
	int GetOrder();
	size_t GetSize();
	std::vector<unsigned> GetAccumulatedFrequencies();
	virtual ~MarkovChain();

};

#endif	/* MARKOVCHAIN_H */

