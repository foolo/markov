#ifndef MARKOVSTATE_H
#define	MARKOVSTATE_H

#include <vector>
#include <string>
#include "Dictionary.h"

class MarkovState
{
private:
	std::vector<id_t> m_ids;

public:
	MarkovState(const std::vector<id_t>& ids);
	bool operator<(MarkovState rhs) const;

	std::string DebugToString(Dictionary &dict) const;
	const std::vector<id_t>& GetIds() const;
};

#endif	/* MARKOVSTATE_H */

