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

*/

#include "HashTable.hpp"
#include "HashMap.hpp"
#include "UnorderedSet.hpp"
#include <string>
#include <vector>
#include <chrono>

namespace tacl
{
	class HashMapWrapper
	{
		HashMap<std::string, tacl::UnorderedSet<unsigned int>> m_table;
	    std::vector<std::string> m_dataVector;

	public:

		HashMapWrapper(const std::string& words);
		bool searchHashMap(const std::string& value);
		bool replaceHashMap(const std::string& value, const std::string& newValue);
		bool extractHashMap(const std::string& value);

	};

	tacl::HashMapWrapper::HashMapWrapper(const std::string& words)
	{
		std::cout << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		getStringData(words, m_dataVector, m_table);

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "AVLMap initialization run time in micro seconds: " << duration.count() << std::endl;
	}

	bool tacl::HashMapWrapper::searchHashMap(const std::string& target)
	{
		
	}

	bool tacl::HashMapWrapper::replaceHashMap(const std::string& target, const std::string& replacement)
	{
		return false;
	}

	bool tacl::HashMapWrapper::extractHashMap(const std::string& target)
	{
		return false;
	}


}