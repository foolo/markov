#ifndef STATERANGE_H
#define	STATERANGE_H

#include <map>
#include "MarkovState.h"

typedef std::map<MarkovState, int> StateFreqMap_t;

class StateRange
{
	StateFreqMap_t::iterator m_stateFreqStart;
	StateFreqMap_t::iterator m_stateFreqEnd;
public:
	StateRange(StateFreqMap_t::iterator start, StateFreqMap_t::iterator end);
	int GetTotalFrequency();
	MarkovState GetStateAtProbability(int p);
	StateFreqMap_t::difference_type Size();
};

#endif	/* STATERANGE_H */

