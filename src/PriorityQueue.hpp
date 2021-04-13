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
#include <iostream>
#include <exception>
#include <string>
#include "Library.hpp"

namespace tacl
{
    template<typename T, typename C = std::less<T>> // default as max heap
    class PriorityQueue
    {
        // Variables
        bool m_descending;
        int m_size;
        int m_count;
        T* m_arr;

        void increaseSize();
        void copy(const PriorityQueue& rhs);

    public:

        // Fuctions
        PriorityQueue(bool m_descending = false);
        PriorityQueue(const PriorityQueue& rhs);
        PriorityQueue& operator=(const PriorityQueue& rhs);
        ~PriorityQueue();
        void insert(const T& data);
        T top(const T& data);
        bool extract(const T& data);
    };

    template<typename T, typename C>
    PriorityQueue<T, C>::PriorityQueue(bool descending)
    {
        m_descending = descending;
        m_count = 0;
        m_size = 16;
        m_arr = new T[m_size];
    }

    template<typename T, typename C>
    PriorityQueue<T,C>::PriorityQueue(const PriorityQueue& rhs)
    {
        copy(rhs);
    }

    template<typename T, typename C>
    PriorityQueue<T,C>& PriorityQueue<T, C>::operator=(const PriorityQueue<T,C>& rhs)
    {
        delete[] m_arr;
        copy(rhs);

        return *this;
    }

    template<typename T, typename C>
    PriorityQueue<T, C>::~PriorityQueue()
    {
        delete[] m_arr;
        m_arr = nullptr;
    }

    template<typename T, typename C>
    void PriorityQueue<T, C>::increaseSize()
    {
        T* temp = tacl::copy(m_arr, m_size, m_size * 2);

        delete[] m_arr;
        m_arr = temp;
    }

    template<typename T, typename C>
    void PriorityQueue<T, C>::copy(const PriorityQueue<T,C>& rhs)
    {
        m_arr = tacl::copy(rhs.m_arr, rhs.m_count, rhs.m_size);
        m_count = rhs.m_count;
        m_size = rhs.m_size;
    }

    template<typename T, typename C>
    void PriorityQueue<T, C>::insert(const T& data)
    {
        if (m_count == m_size)
            increaseSize();

        int arr[m_count] = data;

        for (int i = m_count - 1; i > 0; i--)
        {
            if (C(m_arr[i - 1], m_arr[i])) // the order enforces the fact that less<T> makes a minheap
            {
                m_arr[i] = data;
                m_count++;
                break;
            }

            m_arr[i] = m_arr[i - 1];
        }
    }

    template<typename T, typename C>
    T PriorityQueue<T, C>::top(const T& data)
    {
        if (m_count == 0)
        {
            throw std::exception();
        }
        else
        {
            return m_arr[m_count - 1];
        }
    }

    template<typename T, typename C>
    bool PriorityQueue<T, C>::extract(const T& data)
    {
        if (m_count > 0)
        {
            m_count--;
            return true;
        }

        return false;
    }
}
