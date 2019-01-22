#ifndef MARKOVCHAIN_H
#define	MARKOVCHAIN_H

#include <vector>
#include <ostream>
#include <istream>
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
	StateFreqList_t GetFirstStates();
	void ZeroPad(std::vector<id_t>& firstWords);
	StateRange GetRange(std::vector<id_t> firstWords);
	int GetOrder();
	size_t GetSize();
	std::vector<unsigned> GetAccumulatedFrequencies(); //TODO needed?
	virtual ~MarkovChain();
	void serialize(std::ostream &s);
	static MarkovChain deserialize(std::istream &s);

};

#endif	/* MARKOVCHAIN_H */
