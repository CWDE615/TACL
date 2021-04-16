/*
MIT License
<<<<<<< HEAD

Copyright (c) 2021 Christopher William Driggers-Ellis

=======
Copyright (c) 2021 Christopher William Driggers-Ellis
>>>>>>> 7485c368bd2586704da0ce68350a7653128d3dbe
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
<<<<<<< HEAD

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

=======
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
>>>>>>> 7485c368bd2586704da0ce68350a7653128d3dbe
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
<<<<<<< HEAD
#include <string>
=======
#include <functional> // required for std::greater and std::less
#include <exception>
#include "Library.hpp"
>>>>>>> 7485c368bd2586704da0ce68350a7653128d3dbe

namespace tacl
{
	template<typename T>
	class Heap
	{
		// Variables
<<<<<<< HEAD
		bool m_descending;
		int m_size;
		int m_count;
=======
		bool m_MAX;
		unsigned int m_size;
		unsigned int m_count;
>>>>>>> 7485c368bd2586704da0ce68350a7653128d3dbe
		T* m_heap;

		// Private Funcitons
		void heapifyUp(int index);
		void heapifyDown(int index);
<<<<<<< HEAD
	public:
		// Public Funcitons
		Heap();
		~Heap();
		bool insert(T& data);
		T& top(T& data);
		bool extract(T& data);
=======
		void increaseSize();
		void copy(const Heap& rhs);

	public:
		// Public Funcitons
		Heap(bool max = true);
		Heap(const Heap& rhs);
		Heap& operator=(const Heap& rhs);
		~Heap();

		void insert(T& data);
		T top();
		bool extract();
		unsigned int size();
>>>>>>> 7485c368bd2586704da0ce68350a7653128d3dbe

	};


	template<typename T>
<<<<<<< HEAD
	Heap<T>::Heap()
	{
		m_descending = false;
=======
	Heap<T>::Heap(bool max) : m_MAX(max)
	{
>>>>>>> 7485c368bd2586704da0ce68350a7653128d3dbe
		m_size = 16;
		m_count = 0;
		m_heap = new T[m_size];
	}

	template<typename T>
<<<<<<< HEAD
=======
	Heap<T>::Heap(const Heap<T>& rhs) : m_MAX(rhs.m_MAX)
	{
		copy(rhs);
	}

	template<typename T>
	Heap<T>& Heap<T>::operator=(const Heap<T>& rhs)
	{
		delete[] m_heap;
		copy(rhs);

		return *this;
	}

	template<typename T>
>>>>>>> 7485c368bd2586704da0ce68350a7653128d3dbe
	Heap<T>::~Heap()
	{
		delete[] m_heap;
		m_heap = nullptr;
	}

	template<typename T>
	void Heap<T>::heapifyUp(int index)
	{
<<<<<<< HEAD
		
	}

	template<typename T>
	void Heap<T>::heapifyDown(int index)
	{

		
	}

	template<typename T>
	bool Heap<T>::insert(T& data)
	{
		return false;
	}

	template<typename T>
	T& Heap<T>::top(T& data)
	{
		if (m_count == 0)
		{
			throw exception("m_size of Queue is Empty!");
		}
		else
		{
			return m_arr[m_count - 1];
		}
	}

	template<typename T>
	bool Heap<T>::extract(T& data)
	{
		
=======
		while (index != 0)
		{
			bool up = false;
			if (m_MAX)
			{
			    up = (m_heap[index] > m_heap[(index - 1) / 2]);
			}
			else
			{
				up = (m_heap[index] < m_heap[(index - 1) / 2]);
			}

			if (up)
			{
				T temp = m_heap[index];
				m_heap[index] = m_heap[(index - 1) / 2];
				m_heap[(index - 1) / 2] = temp;
			}
			else
			{
				break;
			}

			index = (index-1)/2;
		}
	}

	/* Heapify down algorithm derived from Christopher's submission to Stepik exercise 6.1.1 */
	template<typename T>
	void Heap<T>::heapifyDown(int index)
	{
		if (2 * index + 1 >= m_count)
			return;

		int next;
		if (2 * index + 2 >= m_count) // check whether the current elemnt has a right child in the heap
		{
			next = 2 * index + 1;    // if the right child is not in the heap, then the left is
		}                            // if neither were, it would be caught above
		else // both are in range of the heap
		{
			bool left = false;
			if (m_MAX)
			{
				left = (m_heap[2 * index + 1] > m_heap[2 * index + 2]);
			}
			else
			{
				left = (m_heap[2 * index + 1] < m_heap[2 * index + 2]);
			}
			
			// the next index is 2*index + 1 or 2*index + 2, which ever has the appropriate entry
			next = (left ? 2 * index + 1 : 2 * index + 2);
		}

		bool go = false;
		if (m_MAX)
		{
			go = (m_heap[index] < m_heap[next]);
		}
		else
		{
			go = (m_heap[index] > m_heap[next]);
		}

		if (go)
		{
			T temp = m_heap[index];
			m_heap[index] = m_heap[next];
		    m_heap[next] = temp;
			heapifyDown(next);  // call the recursive function on the next index.
		}

	}

	template<typename T>
	void Heap<T>::increaseSize()
	{
		T* temp = tacl::copy(m_heap, m_size, m_size * 2);

		m_size *= 2;
		delete[] m_heap;
		m_heap = temp;
	}

	template<typename T>
	void Heap<T>::copy(const Heap& rhs)
	{
		m_heap = tacl::copy(rhs.m_heap, rhs.m_count, rhs.m_size);
		m_count = rhs.m_count;
		m_size = rhs.m_size;
	}

	template<typename T>
	void Heap<T>::insert(T& data)
	{
		m_heap[m_count] = data;
		heapifyUp(m_count);
		m_count++;

		if (m_count == m_size)
			increaseSize();
	}

	template<typename T>
	T Heap<T>::top()
	{
		if (m_count == 0)
			throw std::exception();
		else
			return m_heap[0];
	}

	template<typename T>
	bool Heap<T>::extract()
	{
		if (m_count == 0)
			return false;

		m_heap[0] = m_heap[--m_count];
		heapifyDown(0);
		return true;
	}

	template<typename T>
	unsigned int Heap<T>::size()
	{
		return m_count;
>>>>>>> 7485c368bd2586704da0ce68350a7653128d3dbe
	}

}