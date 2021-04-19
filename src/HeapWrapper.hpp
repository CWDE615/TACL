#pragma once
/*
MIT License

Copyright (c) 2021 Christopher William Driggers-Ellis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include "Heap.hpp" // Heap.hpp contains the functionality of the heap data structure
#include "PriorityQueue.hpp" // PriorityQueue.hpp contains the functionality of the priority queue data structure

namespace tacl
{
    // scheme of using a word-frequency pair is heavily inspired by Christopher's submission to Project 2. 
    // However, no code was directly copied.
    struct WordFreqPair
    {
        std::string m_word;
        unsigned int m_freq;

        WordFreqPair();
        WordFreqPair(const std::string& word, const unsigned int freq);
    };
    
    // constructors
    WordFreqPair::WordFreqPair() : m_word(""), m_freq(0) {}
    WordFreqPair::WordFreqPair(const std::string& word, const unsigned int freq) : m_word(word), m_freq(freq) {}

    // greater than operator
    bool operator>(const WordFreqPair& a, const WordFreqPair& b)
    {
        return a.m_freq > b.m_freq;
    }

    // less than operator
    bool operator<(const WordFreqPair& a, const WordFreqPair& b)
    {
        return a.m_freq < b.m_freq;
    }

    // greater than or equal to operator
    bool operator>=(const WordFreqPair& a, const WordFreqPair& b)
    {
        return a.m_freq >= b.m_freq;
    }

    // less than or equal to operator
    bool operator<=(const WordFreqPair& a, const WordFreqPair& b)
    {
        return a.m_freq <= b.m_freq;
    }

    class HeapWrapper
    {
        tacl::Heap<WordFreqPair> m_heap;
        tacl::PriorityQueue<WordFreqPair> m_pq;
        std::vector<std::string> m_dataVectorHeap;
        std::vector<std::string> m_dataVectorPQ;
        std::string m_filename;

        std::unordered_map<std::string, unsigned int> generateFreqMap(const std::vector<std::string>& input);
        void generateFreqHeap(const std::unordered_map<std::string, unsigned int>& letter_map);
        void generateFreqPQ(const std::unordered_map<std::string, unsigned int>& letter_map);
        bool mostFrequentWordsHeap(int most);
        bool mostFrequentWordsPQ(int most);

    public:
        HeapWrapper(std::string& words, std::string filename, bool pq);
        ~HeapWrapper();

        bool mostFrequentWords(int most, bool pq = true);
    };

    // fill a frequency map with the data. This function was pulled from Christopher's implementation of the Huffman Tree
    // constructor in Project 2
    std::unordered_map<std::string, unsigned int> HeapWrapper::generateFreqMap(const std::vector<std::string>& input)
    {
        // use a map to find the frequencies of each character in the input string
        std::unordered_map<std::string, unsigned int> letter_map;

        for (const std::string& c : input)
        {
            // emplaces new characters into the map or iterates their counters if the character is
            // already present in the map. This strategy of emplacing new elements to the map and doing something
            // else otherwise is quite useful and I have employed used it frequently
            // in other parts of this project as well as in my submission for
            // Stepik exercise 10.1.1 and again, though I did not realize it, in Stepik exercise 7.1.2
            auto character = letter_map.find(c); // determine whether character is in the heap yet. 

            // increment the frequency of the key if it's in the map and emplace said key if it has not been encountered yet.
            if (character == letter_map.end())
                letter_map.emplace(c, 1);
            else
                character->second++;
        }

        // return the result
        return letter_map;
    }

    // generateFreqHeap is also an edited frequency heap constructor from Christopher's submission to project 2 
    void HeapWrapper::generateFreqHeap(const std::unordered_map<std::string, unsigned int>& letter_map)
    {
        // produce a heap by iterating through the map and emplacing elements therein.
        for (auto iter = letter_map.begin(); iter != letter_map.end(); iter++)
        {
            WordFreqPair temp(iter->first, iter->second);
            m_heap.insert(temp);
        }
    }

    // creates a priority queue of each letter in the letter map
    void HeapWrapper::generateFreqPQ(const std::unordered_map<std::string, unsigned int>& letter_map)
    {
        for (auto iter = letter_map.begin(); iter != letter_map.end(); iter++)
        {
            WordFreqPair temp(iter->first, iter->second);
            m_pq.insert(temp);
        }
    }

    // constructor to test the functionality of the heap/priority queue data structures
    // times the functionality of either
    HeapWrapper::HeapWrapper(std::string& words, std::string filename, bool pq) : m_filename(filename)
    {
        std::cout << std::endl;

        if (!pq)
        {
            using namespace std::chrono;
            auto start = high_resolution_clock::now(); //Times the function

            tacl::getStringData(words, m_dataVectorHeap);
            generateFreqHeap(generateFreqMap(m_dataVectorHeap));

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            std::cout << "Heap initialization run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run
        }
        else
        {
            using namespace std::chrono;
            auto start2 = high_resolution_clock::now(); //Times the function

            tacl::getStringData(words, m_dataVectorPQ);
            generateFreqPQ(generateFreqMap(m_dataVectorPQ));

            auto end2 = high_resolution_clock::now();
            auto duration2 = duration_cast<microseconds>(end2 - start2);
            std::cout << "Priority Queue initialization run time in micro seconds: " << duration2.count() << std::endl; //prints out how long it took the function to run
        }

    }

    // destructor
    HeapWrapper::~HeapWrapper()
    {
    }

    // displays the most frequent words of the passed in string file using either the heap or priority queue
    // also shows the time taken for execution
    inline bool HeapWrapper::mostFrequentWords(int most, bool pq)
    {
        std::cout << std::endl;

        using namespace std::chrono;
        std::cout << "~~~ Word Frequency ~~~" << std::endl;
        auto start = high_resolution_clock::now(); //Times the function
        if (pq)
            mostFrequentWordsPQ(most);
        else
            mostFrequentWordsHeap(most);

        auto end = high_resolution_clock::now();

        std::cout << "Top " << most << " words determined." << std::endl;
        std::cout << "~~~ Word Frequency ~~~" << std::endl << std::endl;
        auto duration = duration_cast<microseconds>(end - start);
        std::cout << "Word finding time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run
       
        return true; // returns true if the function was successful
    }

    // helper function that finds the most frequent words in the heap
    // returns true if the function was successful
    bool HeapWrapper::mostFrequentWordsHeap(int words)
    {
        if (words > m_heap.size())
        {
            return false;
        }
        else if (words == 0)
        {
            return false;
        }

        std::ofstream file(m_filename, std::ios_base::app);

        file << "The top " << words << " most frequently used words in input file:" << std::endl;
        file << "#Rank-Word  Frequency" << std::endl;
        for (int i = 1; i <= words; i++)
        {
            WordFreqPair top = m_heap.top(); // avoid copying the top twice
            file << "#" << i << "-" << top.m_word << "  " << top.m_freq << std::endl;
            m_heap.extract();
        }

        file << std::endl;

        file.close();
        return true;
    }

    // helper function that finds the most frequent words in the priority queue
    // returns true if the function was successful
    bool HeapWrapper::mostFrequentWordsPQ(int words)
    {
        if (words > m_pq.size())
        {
            return false;
        }
        else if (words == 0)
        {
            return false;
        }

        std::ofstream file(m_filename, std::ios_base::app);

        file << "The top " << words << " most frequently used words in " << m_filename << ":" << std::endl;
        file << "#Rank-Word  Frequency" << std::endl;
        for (int i = 1; i <= words; i++)
        {
            WordFreqPair top = m_pq.top(); // avoid copying the top twice
            file << "#" << i << "-" << top.m_word << "  " << top.m_freq << std::endl;
            m_pq.extract();
        }

        file << std::endl;

        file.close(); // close the file when finished
        return true;
    }
}