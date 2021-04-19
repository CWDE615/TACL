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

#include <functional>
#include <exception>
#include "Library.hpp" // Library.hpp is responsible for handling the files and their contents

namespace tacl
{
    template<typename T> 
    class PriorityQueue // default as max heap
    {
        unsigned int m_size;
        unsigned int m_count;
        const bool m_MAX;
        T* m_arr;

        void increaseSize(); // increases the size of the priority queue when necessary
        void copy(const PriorityQueue& rhs);

    public:

        PriorityQueue(bool max = true); // constructor
        PriorityQueue(const PriorityQueue& rhs); // copy constructor
        PriorityQueue& operator=(const PriorityQueue& rhs); // copy assignment operator
        ~PriorityQueue(); // destructor

        void insert(const T& data); // insert into priority queue
        T top(); // first element in the priority queue
        bool extract(); // extracts and element from the priority queue
        unsigned int size(); // current size of the priority queue
    };

    // creates a default size array that will be used as a priority queue with 0 elements and a size of 16
    template<typename T>
    PriorityQueue<T>::PriorityQueue(bool max) : m_MAX(max)
    {
        m_count = 0;
        m_size = 16;
        m_arr = new T[m_size];
    }

    // copy constructor
    template<typename T>
    PriorityQueue<T>::PriorityQueue(const PriorityQueue& rhs) : m_MAX(rhs.m_MAX)
    {
        copy(rhs);
    }

    // copy assignment operator
    template<typename T>
    PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& rhs)
    {
        delete[] m_arr;
        copy(rhs);

        return *this;
    }

    // destructor: deletes the no longer necessary array and deallocates the memory
    template<typename T>
    PriorityQueue<T>::~PriorityQueue()
    {
        delete[] m_arr;
        m_arr = nullptr;
    }

    // increases the size of the array for priority queue when more elements are needed
    template<typename T>
    void PriorityQueue<T>::increaseSize()
    {
        T* temp = tacl::copy(m_arr, m_size, m_size * 2); // creating an array double the size using the copy constructor

        m_size *= 2;
        delete[] m_arr; // delete the old array
        m_arr = temp; // the new pointer points to the newly created array
    }

    // copies the content of the passed in priority queue into the current priority queue
    template<typename T>
    void PriorityQueue<T>::copy(const PriorityQueue<T>& rhs)
    {
        m_arr = tacl::copy(rhs.m_arr, rhs.m_count, rhs.m_size);
        m_count = rhs.m_count;
        m_size = rhs.m_size;
    }

    // inserts the data element into the priority queue adjusts size as necessary
    template<typename T>
    void PriorityQueue<T>::insert(const T& data)
    {
        if (m_count == m_size) // increase the size as necessary
            increaseSize();

        int i;
        for (i = m_count; i > 0; i--)
        {
            bool stop = false;
            if (m_MAX)
            {
                stop = m_arr[i - 1] < data; // stop if the element is less than the data
            }
            else
            {
                stop = m_arr[i - 1] > data; // stop if the element is greater than the data
            }

            if (stop)
            {
                m_arr[i] = data; // insert the data into the priority queue
                m_count++;
                break;
            }

            m_arr[i] = m_arr[i - 1];
        }

        if (i == 0) // adds the data at the first position otherwise
        {
            m_arr[0] = data;
            m_count++;
        }
    }

    // gets the first element in the priority queue
    template<typename T>
    T PriorityQueue<T>::top()
    {
        if (m_count == 0)
        {
            throw std::exception(); // if there are no elements throw an exception
        }
        else
        {
            return m_arr[m_count - 1]; // return the element
        }
    }

    // extracts an element from the front of the priority queue by changing the count
    template<typename T>
    bool PriorityQueue<T>::extract()
    {
        if (m_count > 0)
        {
            m_count--;
            return true; // returns true if there was an element to remove
        }

        return false; // returns false if there was no element
    }

    // returns the current size of the priority queue
    template<typename T>
    unsigned int PriorityQueue<T>::size()
    {
        return m_count;
    }
}
