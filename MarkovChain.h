#ifndef MARKOVCHAIN_H
#define	MARKOVCHAIN_H

#include <vector>
#include "Dictionary.h"
#include "MarkovState.h"

class StateRange;

class MarkovChain
{
private:
	std::map<MarkovState, int> m_stateFrequencies;
	unsigned m_markovOrder;

public:
	MarkovChain(int markovOrder);
	void RegisterState(const MarkovState& state);
	int DebugGetFrequency(const MarkovState& state);
	std::vector<std::pair<MarkovState, int>> DebugGetStatesByFrequency();
	void ZeroPad(std::vector<int>& firstWords);
	StateRange GetRange(std::vector<int> firstWords);
	int GetOrder();
	size_t GetSize();
	std::vector<unsigned> GetAccumulatedFrequencies();
	virtual ~MarkovChain();

};

#endif	/* MARKOVCHAIN_H */

