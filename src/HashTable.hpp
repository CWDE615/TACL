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

#pragma once
#include <forward_list>
#include <iostream>
#include <string>
#include <vector>
#include "Library.hpp"

/* Hash Table implementation derived from Christopher William Driggers-Ellis' submission to Stepik 10.2.1
   and retooled by both Corey and Christopher. */
namespace tacl
{
	template<typename T>
	class HashTable
	{

	protected:

		const double m_MAX_FACTOR = 0.6;
		std::forward_list<T>* m_table;
		unsigned int m_count;
		unsigned int m_tableSize;

		//helpers
		double getLoadFactor() const;
		virtual unsigned int hash(T data);
		virtual void rehash();

		std::forward_list<T>* copyTable();
		virtual void copy(const HashTable& rhs);
		unsigned int getCount();
		unsigned int size();

	public:

		HashTable();
		HashTable(const HashTable& rhs);
		HashTable& operator=(const HashTable& rhs);
		virtual ~HashTable();

		virtual bool insert(T data);
		virtual bool find(T data);
		virtual T search(T data);
		virtual bool remove(T data);

	};

	//constructs the hash table with a default size of 31, and a count of 0
	template<typename T>
	HashTable<T>::HashTable()
	{
		m_count = 0;
		m_tableSize = 31;

		m_table = new std::forward_list<T>[m_tableSize];
	}

	template<typename T>
	HashTable<T>::HashTable(const HashTable& rhs)
	{
	    copy();
	}

	//Operator overloader, fairly straight forward and self explanatory.
	template<typename T>
	HashTable<T>& HashTable<T>::operator=(const HashTable<T>& rhs)
	{
		copy();
		return *this;
	}

	template<typename T>
	inline HashTable<T>::~HashTable()
	{
		delete[] m_table;
		m_table = nullptr;
	}

	//Helper function for operator overloarder.
	template<typename T>
	unsigned int HashTable<T>::getCount() 
	{
		return m_count;
	}

	//Helper function for operator overloarder.
	template<typename T>
	std::forward_list<T>* HashTable<T>::copyTable() 
	{
		return tacl::copy(m_table, m_tableSize, m_tableSize);
	}

	template<typename T>
	void HashTable<T>::copy(const HashTable& rhs)
	{
		m_table = rhs.copyTable();
		m_count = rhs.getCount();
		m_tableSize = rhs.size();
	}

	//Returns the current load factor of the hash table. Load factor is calculated by number of elements within the Hashtable divided by the tables size.
	template<typename T>
	double HashTable<T>::getLoadFactor() const
	{
		return ((double)m_count) / m_tableSize;

	}

	template<typename T>
	unsigned int HashTable<T>::hash(T data)
	{
		return std::hash<T>(data) % m_tableSize;
	}


	//If (Load factor is >= MaxFactor) Increases the table size by times 2 plus 1 (to keep it prime), and rehashes all the keys
	template<typename T>
	void HashTable<T>::rehash()
	{
		unsigned int tempSize = m_tableSize;
		m_tableSize = m_tableSize * 2 + 1;
		std::forward_list<T>* tempArr = m_table;
		m_table = new std::forward_list<T>[m_tableSize];

		for (unsigned int i = 0; i < tempSize; i++) 
		{ 
			m_table[i] = tempArr[i];
		}

	}

	//Inserts new keys into the table
	template<typename T>
	bool HashTable<T>::insert(T data)
	{
		if (!find(data)) // if the key does not exist within the Table, create one and push back the 
		{
			m_table[hash(data)].emplace_front(data);
			return true;
		}
		else
		{
			return false;
		}

		m_count++;

		if (getLoadFactor() >= m_MAX_FACTOR)
		{
			rehash();
		}
	}

	// finds element in the hash table
	template<typename T>
	bool HashTable<T>::find(T data)
	{
		unsigned int hashVal = hash(data);
		for (auto finder = m_table[hashVal].begin(); finder != m_table[hashVal].end(); finder++)
		{
			if (*finder == data)
			{
				return true;
			}
		}
		return false;
	}

	// finds element in the has table and returns a copy
	template<typename T>
	T HashTable<T>::search(T data)
	{
		if (!find(data))
			throw std::exception("Element not found");

		unsigned int hashVal = hash(data);
		for (auto finder = m_table[hashVal].begin(); finder != m_table[hashVal].end(); finder++)
		{
			if (*finder == data)
			{
				return *finder;
			}
		}
	}

	template<typename T>
	inline bool HashTable<T>::remove(T data)
	{
		if (!find(data))
			return false;

		int hashVal = hash(data);
		bool exists = false;

		for (auto finder = m_table[hashVal].begin(); finder != m_table[hashVal].end(); finder++)
		{
			if (*finder == data)
			{
				m_count--;
				m_table[hashVal].erase(T);
                exists = true;
				break;
			}
		}

		return exists;

	}

	//returns the size of the table in the form of a count integer
	template<typename T>
	unsigned int HashTable<T>::size()
	{
		return m_tableSize;
	}
}
