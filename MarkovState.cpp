#include "MarkovState.h"
#include <sstream>

bool MarkovState::operator<(MarkovState rhs) const
{
	if (m_ids.size() != rhs.m_ids.size())
	{
		return m_ids.size() < rhs.m_ids.size();
	}

	for (size_t i = 0; i < m_ids.size(); i++)
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

std::string MarkovState::DebugToString(Dictionary &dict) const
{
	std::ostringstream ss;
	for (auto pId = m_ids.begin(); pId != m_ids.end(); pId++)
	{
		ss << *pId << " ";
	}
	ss << "     ";
	for (auto pId = m_ids.begin(); pId != m_ids.end(); pId++)
	{
		std::string word = dict.SearchWordForId(*pId);
		ss << word << " ";
	}
	return ss.str();
}

const std::vector<int>& MarkovState::DebugGetIds() const
{
	return m_ids;
}

MarkovState::MarkovState(const std::vector<int>& ids) :
m_ids(ids)
{
}
