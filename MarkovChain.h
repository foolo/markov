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
};

class MarkovChain
{
private:
	std::map<MarkovState, int> m_stateFrequencies;

public:
	MarkovChain();
	void RegisterState(const MarkovState& state);
	virtual ~MarkovChain();

};

#endif	/* MARKOVCHAIN_H */

