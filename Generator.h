#ifndef GENERATOR_H
#define	GENERATOR_H

#include "MarkovChain.h"
#include "Dictionary.h"


class Generator
{
private:
	MarkovChain &m_markovChain;

public:
	Generator(MarkovChain& markovChain);
	std::vector<id_t> Generate(unsigned count, Dictionary& dictionary);
	virtual ~Generator();
private:
	std::vector<id_t> GetLastN(const std::vector<id_t>& v);
};

#endif	/* GENERATOR_H */

