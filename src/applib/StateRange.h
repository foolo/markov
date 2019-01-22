#pragma once

#include <vector>
#include "Types.h"
#include "MarkovState.h"

class MarkovState;
class Dictionary;

class StateRange
{
private:
	std::vector<StateFreq>::iterator m_stateFreqStart;
	std::vector<StateFreq>::iterator m_stateFreqEnd;

public:
	StateRange(std::vector<StateFreq>::iterator start, std::vector<StateFreq>::iterator end);
	freq_t GetTotalFrequency();
	MarkovState GetStateAtProbability(freq_t p);
	std::vector<StateFreq>::difference_type Size();
	void print(Dictionary& dictionary, id_t lastRelevantId);
};
