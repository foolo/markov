#ifndef STATERANGE_H
#define	STATERANGE_H

#include "Types.h"

class MarkovState;

class StateRange
{
private:
	StateFreqMap_t::iterator m_stateFreqStart;
	StateFreqMap_t::iterator m_stateFreqEnd;

public:
	StateRange(StateFreqMap_t::iterator start, StateFreqMap_t::iterator end);
	freq_t GetTotalFrequency();
	MarkovState GetStateAtProbability(freq_t p);
	StateFreqMap_t::difference_type Size();
};

#endif	/* STATERANGE_H */
