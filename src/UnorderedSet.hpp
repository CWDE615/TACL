#pragma once
#include "HashTable.hpp"

namespace tacl
{
	template<typename T>
	class UnorderedSet : public HashTable<T>
	{
	public:
		UnorderedSet();
		~UnorderedSet();

		static UnorderedSet setUnion(const UnorderedSet& a, const UnorderedSet& b);
		static UnorderedSet setIntersection(const UnorderedSet& a, const UnorderedSet& b);
		static UnorderedSet setDifference(const UnorderedSet& a, const UnorderedSet& b);
	};

	template<typename T>
	UnorderedSet<T>::UnorderedSet() : HashTable<T>() {}

	template<typename T>
	UnorderedSet<T>::~UnorderedSet() {}

	template<typename T>
	UnorderedSet<T> UnorderedSet<T>::setUnion(const UnorderedSet& a, const UnorderedSet& b)
	{
		UnorderedSet<T> res = a;

		for (int i = 0; i < b.m_tableSize; i++)
			for (auto iter = b.m_table[i].begin(); iter != b.m_table[i].end(); iter++)
			    res.insert(*iter); // inserts all elements, but this fails if a had it.

		return res;
	}

	template<typename T>
	UnorderedSet<T> UnorderedSet<T>::setIntersection(const UnorderedSet& a, const UnorderedSet& b)
	{
		UnorderedSet<T> res;

		for (int i = 0; i < a.m_tableSize; i++)
			for (auto iter = a.m_table[i].begin(); iter != a.m_table[i].end(); iter++)
				if (b.find(*iter))
					res.insert(*iter);

		return res;
	}

	template<typename T>
	UnorderedSet<T> UnorderedSet<T>::setDifference(const UnorderedSet& a, const UnorderedSet& b)
	{
		UnorderedSet<T> res = a;

		for (int i = 0; i < b.m_tableSize; i++)
			for (auto iter = b.m_table[i].begin(); iter != b.m_table[i].end(); iter++)
				res.remove(*iter);

		return res;
	}
}