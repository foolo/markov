#include <map>
#include <algorithm>
#include <limits.h>
#include <sstream>
#include <iostream>
#include "MarkovChain.h"

bool MarkovState::operator<(MarkovState rhs) const
{
	if (m_ids.size() != rhs.m_ids.size())
	{
		return m_ids.size() < rhs.m_ids.size();
	}

	for (size_t i = 0; i < m_ids.size(); i++)
	{
		int a = m_ids.at(i);
		int b = rhs.m_ids.at(i);
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
		ss << *pId << " ";
	}
	ss << "     ";
	for (auto pId = m_ids.begin(); pId != m_ids.end(); pId++)
	{
		std::string word = dict.SearchWordForId(*pId);
		ss << word << " ";
	}
	return ss.str();
}

MarkovState::MarkovState(const std::vector<int>& ids) :
m_ids(ids)
{
}

StateRange::StateRange(std::map<MarkovState, int>::iterator start, std::map<MarkovState, int>::iterator end) :
m_start(start), m_end(end)
{
}

MarkovChain::MarkovChain(int markovOrder) :
m_markovOrder(markovOrder)
{
}

void MarkovChain::RegisterState(const MarkovState& state)
{
	m_stateFrequencies[state]++;
}

int MarkovChain::DebugGetFrequency(const MarkovState& state)
{
	return m_stateFrequencies[state];
}

std::vector<std::pair<MarkovState, int> > MarkovChain::DebugGetStatesByFrequency()
{
	std::vector<std::pair<MarkovState, int>> pairs;
	for (auto itr = m_stateFrequencies.begin(); itr != m_stateFrequencies.end(); ++itr)
		pairs.push_back(*itr);

	std::sort(pairs.begin(), pairs.end(), [ = ](const std::pair<MarkovState, int>& a, const std::pair<MarkovState, int>& b){
		return a.second > b.second;
	});
	return pairs;
}

StateRange MarkovChain::GetRange(std::vector<int> firstWords)
{
	// for example  if firstWords == {7, 5, 2}
	//
	// firstWordsLower = {7, 5, 2, 0}
	// firstWordsUpper = {7, 5, 3, 0}   // (note the 3)


	std::vector<int> firstWordsLower(firstWords);
	std::vector<int> firstWordsUpper(firstWords);
	firstWordsUpper.back()++;
	firstWordsLower.push_back(0);
	firstWordsUpper.push_back(0);

	MarkovState lowerState(firstWordsLower);
	MarkovState upperState(firstWordsUpper);

	std::map<MarkovState, int>::iterator start(m_stateFrequencies.lower_bound(lowerState));
	std::map<MarkovState, int>::iterator end(m_stateFrequencies.upper_bound(upperState));
	return StateRange(start, end);
}

int MarkovChain::GetOrder()
{
	return m_markovOrder;
}

size_t MarkovChain::GetSize()
{
	return m_stateFrequencies.size();
}

MarkovChain::~MarkovChain()
{
}

