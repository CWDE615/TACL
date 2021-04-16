#pragma once
#include <string>
#include "Heap.hpp"
#include "PriorityQueue.hpp"

// scheme of using a word-frequncy pair is inspired by Chrstiopher's submission to Project 2. However, no code was
// directly copied.
struct WordFreqPair
{
	std::string m_word;
	unsigned int m_freq;
};

bool operator>(const WordFreqPair& a, const WordFreqPair& b)
{
	return a.m_freq > b.m_freq;
}

bool operator<(const WordFreqPair& a, const WordFreqPair& b)
{
	return a.m_freq < b.m_freq;
}

bool operator>=(const WordFreqPair& a, const WordFreqPair& b)
{
	return a.m_freq >= b.m_freq;
}

bool operator<=(const WordFreqPair& a, const WordFreqPair& b)
{
	return a.m_freq <= b.m_freq;
}

class HashWrapper
{
	

public:
	HashWrapper();
	~HashWrapper();

};

HashWrapper::HashWrapper()
{
}

HashWrapper::~HashWrapper()
{
}

