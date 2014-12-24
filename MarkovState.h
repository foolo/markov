#ifndef MARKOVSTATE_H
#define	MARKOVSTATE_H

#include <vector>
#include <string>
#include "Dictionary.h"

class MarkovState
{
private:
	std::vector<int> m_ids;

public:
	MarkovState(const std::vector<int>& ids);
	bool operator<(MarkovState rhs) const;

	std::string DebugToString(Dictionary &dict) const;
	const std::vector<int>& DebugGetIds() const;
};

#endif	/* MARKOVSTATE_H */

