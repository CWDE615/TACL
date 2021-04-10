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
#include <string>

template<typename T>
class PriorityQueue 
{
    // Variables
    bool m_descending;
    int m_size;
    int m_count;
    T* m_arr;

public:

    // Fuctions
    PriorityQueue(bool m_descending = false);
    ~PriorityQueue();
    void increaseSize();
    void insert(const T& data);
    T& top(const T& data);
    bool extract(const T& data);
};

template<typename T>
PriorityQueue<T>::PriorityQueue(bool descending) 
{
    m_descending = descending;
    m_count = 0;
    m_size = 16;
    m_arr = new T[m_size];
}

template<typename T>
PriorityQueue<T>::~PriorityQueue() 
{
    delete[] m_arr;
    m_arr = nullptr;
}

template<typename T>
void PriorityQueue<T>::increaseSize() 
{
    int newCapacity = capacity * 2;
    T* newArray = new T[newCapacity];
    
    for (int i = 0; i < m_count; i++) 
    {
        newArray[i] = m_arr[i];
    }

    delete[] m_arr;
    m_arr = newArray;
}

template<typename T>
void PriorityQueue<T>::insert(const T& data) {
    
    if (m_count == 0)
        m_arr[0] = data;
    
    for (int i = m_count - 1; i >= 0; i--) 
    {
        bool stop = false;
        if (m_descending)
        {
            stop = arr[i] >= data;
        }
        else
        {
            stop = m_arr[i] <= data;
        }

        m_arr[i + 1] = m_arr[i];

        if (stop)
        {
            m_arr[i] = data;
            break;
        }

        if (i == 0)
            m_arr[0] = data;
    }

    if (m_count == m_size) 
    {
        increaseSize();
    }
}

template<typename T>
T& PriorityQueue<T>::top(const T& data) 
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
bool PriorityQueue<T>::extract(const T& data) 
{

    if (m_count > 0) 
    {
        m_count--;
        return true;
    }

    return false;
}