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

#include <forward_list>
#include <exception>
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include "Library.hpp" // Library.hpp is responsible for handling the files and their contents

/* Hash Table implementation derived from Christopher William Driggers-Ellis' submission to Stepik 10.1.1
   and retooled by both Corey and Christopher. */
namespace tacl
{
	template<typename T>
	class HashTable
	{
	protected:

		const double m_MAX_FACTOR = 0.5;
		std::forward_list<T>* m_table;
		unsigned int m_count;
		unsigned int m_tableSize;

		//helpers
		double getLoadFactor() const;
		virtual void rehash();

		static std::forward_list<T>* copyTable(const HashTable& rhs);
		static unsigned int size(const HashTable& rhs);
		static unsigned int bucketCount(const HashTable& rhs);
		std::forward_list<T>* copyTable();
		virtual void copy(const HashTable& rhs);

	public:

		HashTable();
		HashTable(const HashTable<T>& rhs);
		HashTable& operator=(const HashTable<T>& rhs);
		virtual ~HashTable();

		unsigned int hash(const T& data);
		virtual bool insert(const T& data);
		virtual bool find(const T& data);
		virtual T searchHash(const T& data);
		virtual bool remove(const T& data);

		unsigned int size();
		unsigned int bucketCount();

	};

	//constructs the hash table with a default size of 31, and a count of 0
	template<typename T>
	HashTable<T>::HashTable()
	{
		m_count = 0;
		m_tableSize = 31;

		m_table = new std::forward_list<T>[m_tableSize];
	}

	// hashTable copy constructor
	template<typename T>
	HashTable<T>::HashTable(const HashTable<T>& rhs)
	{
	    copy(rhs);
	}

	// hashTable operator overloader
	template<typename T>
	HashTable<T>& HashTable<T>::operator=(const HashTable<T>& rhs)
	{
		copy(rhs);
		return *this;
	}

	// hashTable destructor
	template<typename T>
	HashTable<T>::~HashTable()
	{
		delete[] m_table; // deallocates the no longer needed array
		m_table = nullptr;
	}

	// copies the content of the passed in HashTable and returns a forward list pointer
	template<typename T>
	std::forward_list<T>* HashTable<T>::copyTable(const HashTable<T>& rhs)
	{
		return tacl::copy(rhs.m_table, rhs.m_tableSize, rhs.m_tableSize);
	}

	// gets the current count of the passed in HashTable
	template<typename T>
	unsigned int HashTable<T>::size(const HashTable<T>& rhs)
	{
		return rhs.m_count;
	}

	// gets the table size (number of buckets) of the passed in HashTable
	template<typename T>
	unsigned int HashTable<T>::bucketCount(const HashTable<T>& rhs)
	{
		return rhs.m_tableSize;
	}

	// Helper function for operator overloarder.
	template<typename T>
	unsigned int HashTable<T>::size() 
	{
		return m_count;
	}

	//Helper function for operator overloarder.
	template<typename T>
	std::forward_list<T>* HashTable<T>::copyTable() 
	{
		return tacl::copy(m_table, m_tableSize, m_tableSize);
	}

	// copies the passed in HashTable information
	template<typename T>
	void HashTable<T>::copy(const HashTable<T>& rhs)
	{
		m_table = copyTable(rhs);
		m_count = size(rhs);
		m_tableSize = bucketCount(rhs);
	}

	// Returns the current load factor of the hash table. Load factor is calculated by number of elements within the HashTable divided by the tables size.
	template<typename T>
	double HashTable<T>::getLoadFactor() const
	{
		return ((double)m_count) / m_tableSize;
	}

	// returns a hash value of the passed in data
	template<typename T>
	unsigned int HashTable<T>::hash(const T& data)
	{
		std::hash<T> hasher;
		return hasher(data) % m_tableSize;
	}


	// If (Load factor is >= MaxFactor) Increases the table size by times 2 plus 1 (to keep it prime), and rehashes all the keys
	template<typename T>
	void HashTable<T>::rehash()
	{
		unsigned int tempSize = m_tableSize;
		m_tableSize = m_tableSize * 2 + 1;
		std::forward_list<T>* tempArr = m_table;
		m_table = new std::forward_list<T>[m_tableSize]; // avoiding collisions

		for (unsigned int i = 0; i < tempSize; i++) 
		{ 
			for (auto iter = tempArr[i].begin(); iter != tempArr[i].end(); iter++)
			{
				insert(*iter); // call the insert function 
				m_count--;
			}
		}

	}

	// Inserts new keys into the table
	template<typename T>
	bool HashTable<T>::insert(const T& data)
	{
		if (!find(data)) // if the key does not exist within the Table, create one and push back the 
		    m_table[hash(data)].emplace_front(data);
		else
	        return false;

		m_count++;

		if (getLoadFactor() >= m_MAX_FACTOR) // rehash if the load factor is greater than or equal to 0.6
		{
			rehash();
		}

		return true;
	}

	// finds element in the hash table
	template<typename T>
	bool HashTable<T>::find(const T& data)
	{
		unsigned int hashVal = hash(data); // get the hash key for the data
		for (auto finder = m_table[hashVal].begin(); finder != m_table[hashVal].end(); finder++)
		{
			if (*finder == data) // if the data is found return true
			{
				return true;
			}
		}
		return false; // the data was not found
	}

	// finds element in the has table and returns a copy
	template<typename T>
	T HashTable<T>::searchHash(const T& data)
	{
		if (!find(data))
			throw std::exception();

		unsigned int hashVal = hash(data);
		for (auto finder = m_table[hashVal].begin(); finder != m_table[hashVal].end(); finder++)
		{
			if (*finder == data) // if the data is in the table return pointed to element
			{
				return *finder;
			}
		}

		return *(m_table[hashVal].begin());
	}

	// removes the data in the hashTable and returns true if it was successfully removed
	template<typename T>
	bool HashTable<T>::remove(const T& data)
	{
		if (!find(data)) // return false if the data is not in the hashTable
			return false;

		int hashVal = hash(data);
		bool exists = false;

		for (auto finder = m_table[hashVal].begin(); finder != m_table[hashVal].end(); finder++)
		{
			if (*finder == data) // data was found
			{
				m_count--;
				// Citation carried over from 10.1.1:
				// I discovered that forward_list in STL allows you to remove an element matching a value
		        // through remove on cppreference.com while checking my syntax for a previous iteration of rem().
		        // This allows us to simplify the task of removing the item from the list by just using the remove()
		        // function on the appropriate list in the array. 
		        // Since the integers inserted are distinct, there is no need to worry about duplicates.
				m_table[hashVal].remove(data);
                exists = true;
				break;
			}
		}

		return exists; // return if the data successfully removed or not

	}

	// returns the size of the table in the form of a count integer
	template<typename T>
	unsigned int HashTable<T>::bucketCount()
	{
		return m_tableSize;
	}

	// takes a passed in string and places each word into the passed in hashTable
	// returns the number of words in the passed in string
	int getStringData(const std::string& value, HashTable<std::string>& table)
	{
		std::istringstream iss(value);
		unsigned int counter = 0;

		std::string word;
		while (getline(iss, word, ' '))
		{
			table.insert(word);
			counter++;
		}

		return counter;
	}
}
