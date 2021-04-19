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

This project was created by the members of Lucky13 for our final project in COP3530.
To request a feature or report bugs, please use our gitHub page.
*/

#include <functional> // required for std::greater and std::less
#include <exception>
#include <sstream>
#include "Library.hpp" // Library.hpp is responsible for handling the files and their contents

namespace tacl
{
	template<typename T>
	class Heap
	{
		// Variables
		bool m_MAX;
		unsigned int m_size;
		unsigned int m_count;
		T* m_heap;

		// Private Functions
		void heapifyUp(int index);
		void heapifyDown(int index);
		void increaseSize();
		void copy(const Heap& rhs);

	public:
		// Public Functions
		Heap(bool max = true);
		Heap(const Heap& rhs);
		Heap& operator=(const Heap& rhs);
		~Heap();

		void insert(T& data);
		T top();
		bool extract();
		unsigned int size();

	};

	// constructor: initial size set to a multiple of 2 with the idea that it will be expanded
	template<typename T>
	Heap<T>::Heap(bool max) : m_MAX(max)
	{
		m_size = 16; 
		m_count = 0;
		m_heap = new T[m_size];
	}

	// copy constructor
	template<typename T>
	Heap<T>::Heap(const Heap<T>& rhs) : m_MAX(rhs.m_MAX)
	{
		copy(rhs);
	}

	// copy assignment operator
	template<typename T>
	Heap<T>& Heap<T>::operator=(const Heap<T>& rhs)
	{
		delete[] m_heap;
		copy(rhs);

		return *this;
	}

	// destructor
	template<typename T>
	Heap<T>::~Heap()
	{
		delete[] m_heap;
		m_heap = nullptr;
	}

	// used when a new element is added to the heap
	template<typename T>
	void Heap<T>::heapifyUp(int index)
	{
		while (index != 0)
		{
			bool up = false;
			if (m_MAX) // compare the current element to its parent
			{
			    up = (m_heap[index] > m_heap[(index - 1) / 2]); 
			}
			else
			{
				up = (m_heap[index] < m_heap[(index - 1) / 2]);
			}

			if (up) // perform the swap 
			{
				T temp = m_heap[index];
				m_heap[index] = m_heap[(index - 1) / 2];
				m_heap[(index - 1) / 2] = temp;
			}
			else // heapify up complete
			{
				break;
			}

			index = (index-1)/2; // continue up the heap
		}
	}

	/* Heapify down algorithm derived from Christopher's submission to Stepik exercise 6.1.1 and similar to Quiz 6 submission as they do the same task */
	template<typename T>
	void Heap<T>::heapifyDown(int index)
	{
		if (2 * index + 1 >= m_count)
			return;

		int next;
		if (2 * index + 2 >= m_count) // check whether the current element has a right child in the heap
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

	// increases the size of the heap using the copy constructor
	template<typename T>
	void Heap<T>::increaseSize()
	{
		T* temp = tacl::copy(m_heap, m_size, m_size * 2); // new heap will be twice the size

		m_size *= 2;
		delete[] m_heap; // delete the old heap
		m_heap = temp;
	}

	// calls the copy constructor to copy the passed in heap to "this" heap
	template<typename T>
	void Heap<T>::copy(const Heap& rhs)
	{
		m_heap = tacl::copy(rhs.m_heap, rhs.m_count, rhs.m_size);
		m_count = rhs.m_count;
		m_size = rhs.m_size;
	}

	// inserts a new item into the heap and calls heapify up
	template<typename T>
	void Heap<T>::insert(T& data)
	{
		m_heap[m_count] = data;
		heapifyUp(m_count);
		m_count++;

		if (m_count == m_size)
			increaseSize(); // increases the size of the heap when necessary
	}

	// gets the topmost element in the heap if there is one
	template<typename T>
	T Heap<T>::top()
	{
		if (m_count == 0)
			throw std::exception(); // throws an exception if there is nothing in the heap
		else
			return m_heap[0];
	}

	// extracts the topmost element in the heap if there is one
	template<typename T>
	bool Heap<T>::extract()
	{
		if (m_count == 0)
			return false; // tells that there was no data in the heap

		m_heap[0] = m_heap[--m_count];
		heapifyDown(0); // reorganizes the heap once the item has been removed
		return true; // returns true if the element was successfully removed
	}

	// gets the current size of the heap
	template<typename T>
	unsigned int Heap<T>::size()
	{
		return m_count;
	}

	// takes a passed in string and places each word into the passed in data vector
	// returns the number of words in the passed in string
	unsigned int getStringData(const std::string& value, std::vector<std::string>& dataVector)
	{
		std::istringstream iss(value);
		unsigned int counter = 0;

		std::string word;
		while (getline(iss, word, ' '))
		{
			dataVector.push_back(word);
			counter++;
		}

		return counter;
	}

}