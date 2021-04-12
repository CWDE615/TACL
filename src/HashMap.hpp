#pragma once
#include "HashTable.hpp"
#include <exception>

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
		
		bool insert(K data, V value);
		V& search(K data);
		bool remove(K data);

		unsigned int size();
		unsigned int bucketCount();
	};

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
				insert(*iter,*val);
				val++;
				this->m_count--;
			}
		}
	}

	template<typename K, typename V>
	HashMap<K,V>::HashMap() : HashTable<K>()
	{
		m_vMirror = new std::forward_list<V>[this->m_tableSize];
	}
	
	template<typename K, typename V>
	HashMap<K,V>::~HashMap()
	{
		delete[] m_vMirror;
		m_vMirror = nullptr;
	}

	template<typename K, typename V>
	bool HashMap<K, V>::insert(K key, V value)
	{
		unsigned int tempSize = this->m_tableSize;

		if (HashTable<K>::find(key))
			return false;


		unsigned int vHash = this->hash(key);
		this->m_table[vHash].emplace_front(key);
		m_vMirror[vHash].emplace_front(value);

		this->m_count++;

		if (this->getLoadFactor() >= this->m_MAX_FACTOR)
		{
			rehash();
		}

		return true;
	}

	template<typename K, typename V>
	V& HashMap<K, V>::search(K key)
	{
		if (!HashTable<K>::find(key))
			throw std::exception();

		unsigned int hashVal = this->hash(key);
		auto val = m_vMirror[hashVal].begin();

		for (auto finder = this->m_table[hashVal].begin(); finder != this->m_table[hashVal].end(); finder++)
		{
			if (*finder == key)
			{
				return *val;
			}

			val++;
		}

	}

	template<typename K, typename V>
	inline bool HashMap<K, V>::remove(K key)
	{
		int hashVal = this->hash(key);
		bool exists = false;
		// according to cplusplus.com, forward list provides a special iterator called before begin
		// which serves as an argument to the functions emplace_after and remove_after.
		auto val = m_vMirror[hashVal].before_begin();

		for (auto finder = this->m_table[hashVal].begin(); finder != this->m_table[hashVal].end(); finder++)
		{
			if (*finder == key)
			{
				this->m_count--;
				this->m_table[hashVal].remove(key);
				m_vMirror[hashVal].erase_after(val);
				exists = true;
				break;
			}

			val++;
		}

		return exists;
	}

	template<typename K, typename V>
	inline unsigned int HashMap<K, V>::size()
	{
		return this->m_count;
	}

	template<typename K, typename V>
	inline unsigned int HashMap<K, V>::bucketCount()
	{
		return this->m_tableSize;
	}


	int getStringData(const std::string& value, std::vector<std::string>& vec, HashMap<std::string,tacl::UnorderedSet<unsigned int>>& table)
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