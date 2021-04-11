#pragma once
#include "HashTable.hpp"

namespace tacl
{
	template<typename K, typename V>
	class HashMap : protected HashTable
	{
	public:
		HashMap();
		~HashMap();
		
		virtual bool insert(K data);
		virtual bool find(K data);
		virtual V search(K data);
		virtual bool remove(K data);

	};
	
	template<typename K, typename V>
	HashMap<K,V>::HashMap()
	{

	}
	
	template<typename K, typename V>
	HashMap<K,V>::~HashMap()
	{
	}

	template<typename K, typename V>
	inline bool HashMap<K, V>::insert(K data)
	{
		return HashTable::insert(std::make_pair(K,V));
	}

	template<typename K, typename V>
	inline bool HashMap<K, V>::find(K data)
	{
		unsigned int hashVal = hash(data);
		for (auto finder = m_table[hashVal].begin(); finder != m_table[hashVal].end(); finder++)
		{
			if (finder->first == data)
			{
				return true;
			}
		}
		return false;
	}

	template<typename K, typename V>
	inline V HashMap<K, V>::search(K data)
	{
		if (!find(data))
			throw std::exception("Element not found");

		unsigned int hashVal = hash(data);
		for (auto finder = m_table[hashVal].begin(); finder != m_table[hashVal].end(); finder++)
		{
			if (finder->left == data)
			{
				return *finder;
			}
		}
	}

	template<typename K, typename V>
	inline bool HashMap<K, V>::remove(K data)
	{
		if (!find(data))
			return false;

		int hashVal = hash(data);
		bool exists = false;

		for (auto finder = m_table[hashVal].begin(); finder != m_table[hashVal].end(); finder++)
		{
			if (finder->first == data)
			{
				m_count--;
				m_table[hashVal].erase(T);
				exists = true;
				break;
			}
		}

		return exists;
	}

	


}