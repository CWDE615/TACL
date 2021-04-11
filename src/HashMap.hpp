#pragma once
#include "HashTable.hpp"

namespace tacl
{
	template<typename K, typename V>
	class HashMap : protected HashTable<std::pair<K,V>>
	{
		unsigned int hash(K key);
	public:
		HashMap();
		~HashMap();
		
		bool insert(K data, V value);
		bool find(K data);
		V search(K data);
		bool remove(K data);

	};
	
	template<typename K, typename V>
	unsigned int HashMap<K, V>::hash(K key)
	{
		return hash<K>(key) % this->m_tableSize;
	}

	template<typename K, typename V>
	HashMap<K,V>::HashMap() : HashTable()
	{
		
	}
	
	template<typename K, typename V>
	HashMap<K,V>::~HashMap()
	{
	}

	template<typename K, typename V>
	bool HashMap<K, V>::insert(K key, V value)
	{
		if (!find(key)) // if the key does not exist within the Table, create one and push back the 
		{
			this->m_table[hash(key)].emplace_front(make_pair(key,value));
			return true;
		}
		else
		{
			return false;
		}

		this->m_count++;

		if (this->getLoadFactor() >= this->m_MAX_FACTOR)
		{
			this->rehash();
		}
	}

	template<typename K, typename V>
	inline bool HashMap<K, V>::find(K key)
	{
		unsigned int hashVal = hash(key);
		for (auto finder = this->m_table[hashVal].begin(); finder != this->m_table[hashVal].end(); finder++)
		{
			if (finder->first == key)
			{
				return true;
			}
		}
		return false;
	}

	template<typename K, typename V>
	inline V HashMap<K, V>::search(K key)
	{
		if (!find(key))
			throw std::exception("Element not found");

		unsigned int hashVal = hash(key);
		for (auto finder = this->m_table[hashVal].begin(); finder != this->m_table[hashVal].end(); finder++)
		{
			if (finder->first == key)
			{
				return *finder;
			}
		}
	}

	template<typename K, typename V>
	inline bool HashMap<K, V>::remove(K key)
	{
		if (!find(key))
			return false;

		int hashVal = hash(key);
		bool exists = false;

		for (auto finder = this->m_table[hashVal].begin(); finder != this->m_table[hashVal].end(); finder++)
		{
			if (finder->first == key)
			{
				this->m_count--;
				this->m_table[hashVal].erase(key);
				exists = true;
				break;
			}
		}

		return exists;
	}

	


}