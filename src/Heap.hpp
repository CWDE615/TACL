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
#include <string>

namespace tacl
{
	template<typename T>
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
	public:
		// Public Funcitons
		Heap();
		~Heap();
		bool insert(T& data);
		T& top(T& data);
		bool extract(T& data);

	};


	template<typename T>
	Heap<T>::Heap()
	{
		m_descending = false;
		m_size = 16;
		m_count = 0;
		m_heap = new T[m_size];
	}

	template<typename T>
	Heap<T>::~Heap()
	{
		delete[] m_heap;
		m_heap = nullptr;
	}

	template<typename T>
	void Heap<T>::heapifyUp(int index)
	{
		
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
		
	}

}