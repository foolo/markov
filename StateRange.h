#ifndef STATERANGE_H
#define	STATERANGE_H

#include <map>
#include "MarkovState.h"

class StateRange
{
public:
	std::map<MarkovState, int>::iterator m_stateFreqStart;
	std::map<MarkovState, int>::iterator m_stateFreqEnd;
	StateRange(std::map<MarkovState, int>::iterator start, std::map<MarkovState, int>::iterator end);
	int GetTotalFrequency();
	MarkovState GetStateAtProbability(int p);
};

#endif	/* STATERANGE_H */

