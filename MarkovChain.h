#ifndef MARKOVCHAIN_H
#define	MARKOVCHAIN_H

#include <vector>
#include "MarkovState.h"
#include "Types.h"

class StateRange;

typedef std::vector<std::pair<MarkovState, freq_t>> StateFreqList_t;

class MarkovChain
{
private:
	StateFreqMap_t m_stateFrequencies;
	unsigned m_markovOrder;

public:
	MarkovChain(int markovOrder);
	void RegisterState(const MarkovState& state);
	freq_t DebugGetFrequency(const MarkovState& state);
	StateFreqList_t GetStatesByFrequency();
	void ZeroPad(std::vector<id_t>& firstWords);
	StateRange GetRange(std::vector<id_t> firstWords);
	int GetOrder();
	size_t GetSize();
	std::vector<unsigned> GetAccumulatedFrequencies();
	virtual ~MarkovChain();

};

#endif	/* MARKOVCHAIN_H */
