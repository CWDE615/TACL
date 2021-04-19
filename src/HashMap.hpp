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

#include "HashTable.hpp" // HashTable.hpp is responsible for creating and storing different occurrences of input data
#include "UnorderedSet.hpp" // UnorderedSet.hpp is responsible for organizing occurrences of the data in HashTable
#include <exception>
#include <sstream>

namespace tacl
{
	template<typename K, typename V>
	class HashMap : protected HashTable<K>
	{
		std::forward_list<V>* m_vMirror;

		void rehash();
	public:
		HashMap();
		~HashMap();
		
		bool insert(const K& data, const V& value);
		V& search(const K& data);
		bool remove(const K& data);

		unsigned int size();
		unsigned int bucketCount();
	};

	// increases the size of the hashmap 
	template<typename K, typename V>
	void HashMap<K, V>::rehash()
	{
		unsigned int tempSize = this->m_tableSize;
		this->m_tableSize = this->m_tableSize * 2 + 1;
		std::forward_list<K>* tempArr = this->m_table;
		std::forward_list<V>* tempMir = m_vMirror;
		this->m_table = new std::forward_list<K>[this->m_tableSize];
		m_vMirror = new std::forward_list<V>[this->m_tableSize];

		for (unsigned int i = 0; i < tempSize; i++)
		{
			auto val = tempMir[i].begin();
			for (auto iter = tempArr[i].begin(); iter != tempArr[i].end(); iter++)
			{
				insert(*iter,*val); // inserts all values into the new hashmap
				val++;
				this->m_count--;
			}
		}
	}

	// constructor with a forward list
	template<typename K, typename V>
	HashMap<K,V>::HashMap() : HashTable<K>()
	{
		m_vMirror = new std::forward_list<V>[this->m_tableSize]; 
	}
	
	// destructor
	template<typename K, typename V>
	HashMap<K,V>::~HashMap()
	{
		delete[] m_vMirror; // deallocates the forward list
		m_vMirror = nullptr;
	}

	// inserts a new element with a key value pair into the hashmap
	template<typename K, typename V>
	bool HashMap<K, V>::insert(const K& key, const V& value)
	{
		if (HashTable<K>::find(key))
			return false; // returns false if the value already exists

		unsigned int vHash = this->hash(key);
		this->m_table[vHash].emplace_front(key); // insert the new key to the front of the key list
		m_vMirror[vHash].emplace_front(value); // insert the new value to the front of the value list

		this->m_count++;

		if (this->getLoadFactor() >= this->m_MAX_FACTOR)
		{
			rehash(); // call the rehash function if the load factor exceeds 0.6
		}

		return true; // return true if the insertion was successful
	}

	// search the hashmap with the passed in key
	template<typename K, typename V>
	V& HashMap<K, V>::search(const K& key)
	{
		if (!HashTable<K>::find(key)) // throw an exception if the key was not found
			throw std::exception();

		unsigned int hashVal = this->hash(key);
		auto val = m_vMirror[hashVal].begin();

		// iterate over the table to find the value
		for (auto finder = this->m_table[hashVal].begin(); finder != this->m_table[hashVal].end(); finder++)
		{
			if (*finder == key)
			{
				return *val; // return the found value
			}

			val++; // increase the value iterator
		}


		return *(this->m_vMirror[hashVal].begin()); // return the first key's value otherwise
	}

	// remove a key from the hashmap if it exists
	template<typename K, typename V>
	bool HashMap<K, V>::remove(const K& key)
	{
		int hashVal = this->hash(key);
		bool exists = false;
		// according to cplusplus.com, forward list provides a special iterator called before begin
		// which serves as an argument to the functions emplace_after and remove_after.
		auto val = m_vMirror[hashVal].before_begin();

		for (auto finder = this->m_table[hashVal].begin(); finder != this->m_table[hashVal].end(); finder++)
		{
			if (*finder == key) // if found
			{
				this->m_count--;
				this->m_table[hashVal].remove(key);
				m_vMirror[hashVal].erase_after(val);
				exists = true;
				break;
			}

			val++;
		}

		return exists; // return true if found, false if not
	}

	// get the current size of the hashMap
	template<typename K, typename V>
	unsigned int HashMap<K, V>::size()
	{
		return this->m_count;
	}

	// get the current bucket count (table size)
	template<typename K, typename V>
	unsigned int HashMap<K, V>::bucketCount()
	{
		return this->m_tableSize;
	}

	
	unsigned int getStringData(const std::string& value, std::vector<std::string>& vec, HashMap<std::string,tacl::UnorderedSet<unsigned int>>& table)
	{
		std::istringstream iss(value);
		unsigned int counter = 0;

		std::string word;
		while (getline(iss, word, ' '))
		{
			vec.push_back(word);

			try
			{
				UnorderedSet<unsigned int>& posSet = table.search(word);
				posSet.insert(counter);
			}
			catch (std::exception& e)
			{
				UnorderedSet<unsigned int> temp;
				temp.insert(counter);
				table.insert(word, temp);
			}

			counter++;
		}

		return counter;
	}
}