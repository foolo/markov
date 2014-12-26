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
	std::vector<int> Generate(unsigned count, Dictionary& dictionary);
	virtual ~Generator();
private:
	std::vector<int> GetLastN(const std::vector<int>& v);
};

#endif	/* GENERATOR_H */

