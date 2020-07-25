#pragma once

#include <vector>
#include <string>
#include <ostream>
#include <istream>
#include "Types.h"

class Dictionary;

class MarkovState
{
private:
	std::vector<id_t> m_ids;

public:
	MarkovState();
	MarkovState(const std::vector<id_t>& ids);
	bool operator<(MarkovState rhs) const;

	std::string DebugToString(Dictionary &dict) const;
	void serialize(std::ostream &s) const;
	void deserialize(std::istream &s, unsigned order);
	const std::vector<id_t>& GetIds() const;
};

struct StateFreq
{
	MarkovState m_state;
	freq_t m_freq;

public:
	StateFreq(const MarkovState &state, freq_t freq);
	bool operator<(MarkovState rhs) const;
};
