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

#pragma once
#include "Library.hpp"

namespace tacl
{
	template<typename T, typename C = std::less<T>>
	class Heap
	{
		// Variables
		bool m_descending;
		int m_size;
		int m_count;
		T* m_heap;

		// Private Funcitons
		void heapifyUp(int index);
		void heapifyDown(int index);
		void increaseSize();
		void copy(const Heap& rhs);

	public:
		// Public Funcitons
		Heap();
		Heap(const Heap& rhs);
		Heap& operator=(const Heap& rhs);
		~Heap();
		void insert(T& data);
		T top(T& data);
		void extract();

	};


	template<typename T, typename C>
	Heap<T,C>::Heap()
	{
		m_descending = false;
		m_size = 16;
		m_count = 0;
		m_heap = new T[m_size];
	}

	template<typename T, typename C>
	Heap<T, C>::Heap(const Heap& rhs)
	{
		copy(rhs);
	}

	template<typename T, typename C>
	Heap<T,C>& Heap<T,C>::operator=(const Heap<T,C>& rhs)
	{
		delete[] m_heap;
		copy(rhs);

		return *this;
	}

	template<typename T, typename C>
	Heap<T,C>::~Heap()
	{
		delete[] m_heap;
		m_heap = nullptr;
	}

	template<typename T, typename C>
	void Heap<T,C>::heapifyUp(int index)
	{
		while (index != 0)
		{
			if (!C(m_heap[index], m_heap[(index - 1) / 2]))
			{
				T temp = m_heap[index];
				m_heap[index] = m_heap[(index - 1) / 2];
				m_heap[(index - 1) / 2] = temp;
			}
			else
			{
				break;
			}
		}
	}

	/* Heapify down algorithm derived from Christopher's submission to Stepik exercise 6.1.1 */
	template<typename T, typename C>
	void Heap<T,C>::heapifyDown(int index)
	{
		int next;
		if (2 * index + 2 >= m_size) // check whether the current elemnt has a right child in the heap
		{
			next = 2 * index + 1;    // if the right child is not in the heap, then the left is
		}                            // if neither were, it would be caught above
		else // both are in range of the heap
		{
			// the next index is 2*index + 1 or 2*index + 2, which ever has a lesser entry
			next = (!C(m_heap[2 * index + 1], m_heap[2 * index + 2]) ? 2 * index + 1 : 2 * index + 2);
		}

		if (C(m_heap[index], m_heap[next]))
		{
			T temp = m_heap[index];
			m_heap[index] = m_heap[next];
		    m_heap[next] = temp;
			heapifyDown(next);  // call the recursive function on the next index.
		}

	}

	template<typename T, typename C>
	void Heap<T, C>::increaseSize()
	{
		T* temp = tacl::copy(m_heap, m_size, m_size * 2);

		delete[] m_heap;
		m_heap = temp;
	}

	template<typename T, typename C>
	void Heap<T, C>::copy(const Heap& rhs)
	{
		m_heap = tacl::copy(rhs.m_heap, rhs.m_count, rhs.m_size);
		m_count = rhs.m_count;
		m_size = rhs.m_size;
	}

	template<typename T, typename C>
	void Heap<T,C>::insert(T& data)
	{
		m_heap[m_count++] = data;
		heapifyUp();

		if (m_count == m_size)
			increaseSize();
	}

	template<typename T, typename C>
	T Heap<T,C>::top(T& data)
	{
		if (m_count == 0)
			throw std::exception();
		else
			return m_heap[0];
	}

	template<typename T, typename C>
	void Heap<T,C>::extract()
	{
		if (m_count = 0)
			throw std::exception();

		m_heap[0] = m_heap[m_size - 1];
		heapifyDown(0);
	}

}