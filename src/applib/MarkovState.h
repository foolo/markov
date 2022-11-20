#pragma once

#include <vector>
#include <string>
#include <ostream>
#include <istream>
#include "Types.h"

class Dictionary;

class MarkovState
{
protected:
	std::vector<id_t> m_ids;

public:
	MarkovState();
	MarkovState(const std::vector<id_t>& ids);
	bool operator<(MarkovState rhs) const;

	std::string DebugToString(Dictionary &dict) const;
	const std::vector<id_t>& GetIds() const;
};

struct StateFreq : public MarkovState
{
	MarkovState m_state;
	freq_t m_freq;

public:
	StateFreq();
	StateFreq(const MarkovState &state, freq_t freq);
	void serialize(std::ostream &s) const;
	void deserialize(std::istream &s, unsigned order);
	bool operator<(MarkovState rhs) const;
};
