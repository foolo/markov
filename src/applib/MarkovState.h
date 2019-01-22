#ifndef MARKOVSTATE_H
#define	MARKOVSTATE_H

#include <vector>
#include <string>
#include <ostream>
#include <istream>

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

#endif	/* MARKOVSTATE_H */
