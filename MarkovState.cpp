#include "MarkovState.h"
#include <sstream>
#include <iomanip>

bool MarkovState::operator<(MarkovState rhs) const
{
	if (m_ids.size() != rhs.m_ids.size())
	{
		return m_ids.size() < rhs.m_ids.size();
	}
	for (size_t i = 0; i < m_ids.size(); i++)
	{
		id_t a = m_ids.at(i);
		id_t b = rhs.m_ids.at(i);
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
		ss << std::setfill(' ') << std::setw(4) << *pId << " ";
	}
	ss << "   ";
	for (auto pId = m_ids.begin(); pId != m_ids.end(); pId++)
	{
		std::string word = dict.SearchWordForId(*pId);
		ss << word << "\t";
	}
	return ss.str();
}

const std::vector<id_t>& MarkovState::GetIds() const
{
	return m_ids;
}

MarkovState::MarkovState(const std::vector<id_t>& ids) :
m_ids(ids)
{
}
