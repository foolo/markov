#include <sstream>
#include <iomanip>
#include "MarkovState.h"
#include "Dictionary.h"
#include "util/SerializeUtils.h"

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
	return false;
}

std::string ToHex(const std::string& s)
{
	std::ostringstream ret;
	for (std::string::size_type i = 0; i < s.length(); ++i)
	{
		ret << " " << std::hex << std::setfill('0') << std::setw(2) << std::nouppercase << (int)(unsigned char) s[i];
	}
	return ret.str();
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

	for (auto pId = m_ids.begin(); pId != m_ids.end(); pId++)
	{
		std::string word = dict.SearchWordForId(*pId);
		ss << "(" << ToHex(word) << ")" << "\t";
	}
	return ss.str();
}

void MarkovState::serialize(std::ostream &s) const {
	s << "ids ";
	for (auto pId = m_ids.begin(); pId != m_ids.end(); pId++) {
		s << *pId << " ";
	}
}

void MarkovState::deserialize(std::istream& s, unsigned order) {
	SerializeUtils::assert(s, "ids");
	for (unsigned i = 0; i < order; i++) {
		id_t id = SerializeUtils::read_unsigned(s);
		m_ids.push_back(id);
	}
}

const std::vector<id_t>& MarkovState::GetIds() const
{
	return m_ids;
}

MarkovState::MarkovState() {
}

MarkovState::MarkovState(const std::vector<id_t>& ids) :
m_ids(ids)
{
}

MarkovStateFreq::MarkovStateFreq(const MarkovState& state, freq_t freq): m_state(state), m_freq(freq) {
}

bool MarkovStateFreq::operator<(MarkovState rhs) const {
	return m_state.operator <(rhs);
}
