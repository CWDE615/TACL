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

This project was created by the members of Lucky13 for our final project in COP3530.
To request a feature or report bugs, please use our gitHub page.
*/

#include "HashTable.hpp" // HashTable.hpp is responsible for creating and storing different occurrences of input data

namespace tacl
{
	template<typename T>
	class UnorderedSet : public HashTable<T>
	{
	public:
		UnorderedSet();
		~UnorderedSet();

		std::vector<T> members();
		static UnorderedSet setUnion(const UnorderedSet& a, const UnorderedSet& b);
		static UnorderedSet setIntersection(const UnorderedSet& a, const UnorderedSet& b);
		static UnorderedSet setDifference(const UnorderedSet& a, const UnorderedSet& b);
	};

	// constructor
	template<typename T>
	UnorderedSet<T>::UnorderedSet() : HashTable<T>() {}

	// destructor
	template<typename T>
	UnorderedSet<T>::~UnorderedSet() {}

	// returns a vector of all the elements in the hashTable
	template<typename T>
	std::vector<T> UnorderedSet<T>::members()
	{
		std::vector<T> res;

		for (int i = 0; i < this->bucketCount(); i++) // each hash key
		{
			std::forward_list<T> temp = this->m_table[i];
			for (auto iter = temp.begin(); iter != temp.end(); iter++) // each occurrence within the hash key
			{
				res.push_back(*iter); // add the occurrence to the vector
			}
		}

		return res; // return the created vector
	}

	// takes in two unordered sets "a" and "b" and performs a union between the two sets
	template<typename T>
	UnorderedSet<T> UnorderedSet<T>::setUnion(const UnorderedSet& a, const UnorderedSet& b)
	{
		UnorderedSet<T> res = a;

		for (int i = 0; i < b.m_tableSize; i++)
			for (auto iter = b.m_table[i].begin(); iter != b.m_table[i].end(); iter++)
			    res.insert(*iter); // inserts all elements, but this fails if a had it.

		return res; // return the new set
	}

	// takes in two unordered sets "a" and "b" and performs an intersection between the two sets
	template<typename T>
	UnorderedSet<T> UnorderedSet<T>::setIntersection(const UnorderedSet& a, const UnorderedSet& b)
	{
		UnorderedSet<T> res;

		for (int i = 0; i < a.m_tableSize; i++)
			for (auto iter = a.m_table[i].begin(); iter != a.m_table[i].end(); iter++)
				if (b.find(*iter))
					res.insert(*iter); // inserts only the elements that are in "a" that also belong to "b"

		return res; // return the new set
	}

	// takes in two unordered sets "a" and "b" and performs a - b set difference
	template<typename T>
	UnorderedSet<T> UnorderedSet<T>::setDifference(const UnorderedSet& a, const UnorderedSet& b)
	{
		UnorderedSet<T> res = a; // assign res set to a

		for (int i = 0; i < b.m_tableSize; i++)
			for (auto iter = b.m_table[i].begin(); iter != b.m_table[i].end(); iter++)
				res.remove(*iter); // remove elements from "a" (res) that are in "b"

		return res; // return the new set
	}
}