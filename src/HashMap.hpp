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
		V search(K data);
		bool remove(K data);

	};

	template<typename K, typename V>
	void HashMap<K, V>::rehash()
	{
		unsigned int tempSize = this->m_tableSize;
		this->m_tableSize = this->m_tableSize * 2 + 1;
		std::forward_list<K>* tempArr = this->m_table;
		this->m_table = new std::forward_list<K>[this->m_tableSize];

		for (unsigned int i = 0; i < tempSize; i++)
		{
			for (auto iter = tempArr.begin(); iter != tempArr.end(); iter++)
			{
				insert(*iter);
				this->m_count--;
			}
		}
	}

	template<typename K, typename V>
	HashMap<K,V>::HashMap() : HashTable<K>()
	{
		m_vMirror = new std::forward_list<K>[this->m_tableSize];
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

		if (!HashTable<K>::insert(key))
			return false;
		
		unsigned int vHash = this->hash(key);
		m_vMirror[vHash].emplace_front(value);

		if (this->m_tableSize > tempSize)
		{
			std::forward_list<V>* temp = tacl::copy(m_vMirror, tempSize, this->m_tableSize);
			delete[] m_vMirror;
			m_vMirror = temp;
		}

		return true;
	}

	template<typename K, typename V>
	V HashMap<K, V>::search(K key)
	{
		if (!find(key))
			throw std::exception();

		unsigned int hashVal = hash(key);
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
		int hashVal = hash(key);
		bool exists = false;
		// according to cplusplus.com, forward list provides a special iterator called before begin
		// which serves as an argument to the functions emplace_after and remove_after.
		auto val = m_vMirror[hashVal].before_begin();

		for (auto finder = this->m_table[hashVal].begin(); finder != this->m_table[hashVal].end(); finder++)
		{
			if (*finder == key)
			{
				this->m_count--;
				this->m_table[hashVal].erase(key);
				m_vMirror[hashVal].erase_after(val);
				exists = true;
				break;
			}

			val++;
		}

		return exists;
	}

}