#ifndef STATERANGE_H
#define	STATERANGE_H

#include "Types.h"
#include "MarkovState.h"

class MarkovState;
class Dictionary;

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
	void print(Dictionary& dictionary, id_t lastRelevantId);
};

#endif	/* STATERANGE_H */
