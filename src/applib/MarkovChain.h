#ifndef MARKOVCHAIN_H
#define	MARKOVCHAIN_H

#include <vector>
#include <ostream>
#include <istream>
#include <map>
#include "MarkovState.h"
#include "Types.h"

class StateRange;

typedef std::vector<StateFreq> StateFreqList_t;

class MarkovChain
{
private:
	std::vector<StateFreq> m_stateFrequencies;
	unsigned m_markovOrder;

public:
	MarkovChain(int markovOrder);
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
	void load_from_map(std::map<MarkovState, freq_t> &map);

};

#endif	/* MARKOVCHAIN_H */
