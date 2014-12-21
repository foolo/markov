#ifndef MARKOVCHAIN_H
#define	MARKOVCHAIN_H

#include <vector>

class MarkovState
{
private:
	std::vector<int> m_ids;

public:
	MarkovState(const std::vector<int>& ids);
	bool operator<(MarkovState rhs) const;

	std::string DebugToString();
};

struct StateRange
{
	std::map<MarkovState, int>::iterator m_start;
	std::map<MarkovState, int>::iterator m_end;
	StateRange(std::map<MarkovState, int>::iterator start, std::map<MarkovState, int>::iterator end);
};

class MarkovChain
{
private:
	std::map<MarkovState, int> m_stateFrequencies;
	int m_markovOrder;

public:
	MarkovChain(int markovOrder);
	void RegisterState(const MarkovState& state);
	int DebugGetFrequency(const MarkovState& state);
	std::vector<std::pair<MarkovState, int>> DebugGetStatesByFrequency();
	StateRange GetRange(std::vector<int> firstWords);
	int GetOrder();
	size_t GetSize();
	virtual ~MarkovChain();

};

#endif	/* MARKOVCHAIN_H */

