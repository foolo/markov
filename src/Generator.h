#pragma once

#include <vector>
#include "Types.h"

class MarkovChain;
class Dictionary;

class Generator
{
private:
	MarkovChain &m_markovChain;

public:
	Generator(MarkovChain& markovChain);
	std::vector<id_t> Generate(unsigned count, Dictionary& dictionary, bool debug);
	virtual ~Generator();
private:
	std::vector<id_t> GetLastN(const std::vector<id_t>& v);
};
