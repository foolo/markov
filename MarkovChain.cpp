#include <map>

#include "MarkovChain.h"

bool MarkovState::operator<(MarkovState rhs) const
{
	if (m_ids.size() != rhs.m_ids.size())
	{
		return m_ids.size() < rhs.m_ids.size();
	}

	for (int i = 0; i < m_ids.size(); i++)
	{
		int a = m_ids.at(i);
		int b = rhs.m_ids.at(i);
		if (a != b)
		{
			return a < b;
		}
	}
	// equal
	return false;
}

MarkovState::MarkovState(const std::vector<int>& ids) :
m_ids(ids)
{
}

MarkovChain::MarkovChain()
{
}

void MarkovChain::RegisterState(const MarkovState& state)
{
	m_stateFrequencies[state]++;
}

MarkovChain::~MarkovChain()
{
}

