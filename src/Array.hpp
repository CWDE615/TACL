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

class Array {
private:
    int capacity;
    int numberOfElements;
    T* arr;

public:
    Array();
    ~Array();
    int size() const;
    void add(const T& obj);
    void increaseSize();
    T& get(int index);
};

template<typename T>
Array<T>::Array() {
    capacity = 1000; // Initial capacity is 1000
    numberOfElements = 0;
    arr = new T[capacity];
}

template<typename T>
Array<T>::~Array() {
    delete[] arr;
    arr = nullptr;
}

template<typename T>
int Array<T>::size() const {
    return numberOfElements;
}

template<typename T>
void Array<T>::increaseSize() {
    int newCapacity = capacity * 2;
    T* newArray = new T[newCapacity];
    
    for (int i = 0; i < numberOfElements; i++) {
        newArray[i] = arr[i];
    }

    delete[] arr;
    arr = newArray;
    newArray = nullptr;
}

template<typename T>
void Array<T>::add(const T& obj) {
    
    if (numberOfElements == capacity) {
        increaseSize();
    }

    arr[numberOfElements] = obj;
    numberOfElements++;
}

template<typename T>
T& Array<T>::get(int index) {

    if (index < 0 || index >= numberOfElements) {
        throw "INVALID INDEX";
    }

    return arr[index];
}