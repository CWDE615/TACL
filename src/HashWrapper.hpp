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

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include "HashTable.hpp"
#include "Library.hpp"

namespace tacl 
{

	class HashWrapper {

	private:
		HashTable<std::string> m_table;


	public:
		HashWrapper(std::string& words); //constructor

		bool searchHashTable(std::string value); //Search functionality

		bool replaceHashTable(std::string value, std::string newValue); //Replace functionality

		bool removeHashTable(std::string value); //Remove functionality

	};

	HashWrapper::HashWrapper(std::string& words) 
	{

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		m_table = HashTable<std::string>();
		getStringData(words, m_table);

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "HashTable construction run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}

	bool HashWrapper::removeHashTable(std::string value) {

		std::cout << std::endl;//ensures spacing between key function printing
		std::cout << "~~~HashTable Removal~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function
		

		std::cout << "Size of HashTable before removal: " << m_table.size() << std::endl;
		std::cout << "Attempting to remove \"" << value << "\"." << std::endl;

		bool removed = m_table.remove(value);

		std::cout << "~~~HashTable Removal~~~" << std::endl;
		std::cout << std::endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "HashTable value removal run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

		return removed;


	}

	bool HashWrapper::replaceHashTable(std::string value, std::string newValue) {

		std::cout << std::endl;//ensures spacing between key function printing
		std::cout << "~~~HashTable Replace~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		bool replaced = m_table.remove(value);
		replaced = replaced && m_table.insert(value);

		if (replaced)
		{
			std::cout << "Replaced " << "\"" << value << "\" with \"" << newValue << "\"." << std::endl;
			std::cout << "~~~HashTable Replace~~~" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << "\"" << value << "\" does not exist or was not replaced." << std::endl;
		}

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "HashTable value replace run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

		return replaced;
	}

	bool HashWrapper::searchHashTable(std::string value) {

		std::cout << std::endl; //ensures spacing between key function printing
		std::cout << "~~~HashTable Search~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		try
		{
			std::string finding = m_table.searchHash(value);
		}
		catch (std::exception& e)
		{
			return false;
		}

		std::cout << "Found \"" << value << "\" within the HashTable!" << std::endl;

		std::cout << "~~~HashTable Search~~~" << std::endl;
		std::cout << std::endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "HashTable value search run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

		return true;
	}
}