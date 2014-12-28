#ifndef TYPES_H
#define	TYPES_H

#include <map>
#include "MarkovState.h"

typedef unsigned id_t;

typedef unsigned long freq_t;

typedef std::map<MarkovState, freq_t> StateFreqMap_t;

enum TextState
{
	inital_state, middle_of_sentence, sentence_ended, sentence_pause
};

#endif	/* TYPES_H */
