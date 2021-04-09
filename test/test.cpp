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
#pragma once
#include <iostream>
#include "Map.hpp"
#include "MapWrapper.hpp"
#include "HashTable.hpp"
#include "HashWrapper.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

namespace tacl {
	TEST_CASE("AVLMap Insert 100k words", "[insert]") //tests insertion of the AVLMap
	{
		std::string words = std::to_string(0); //This test inserts 0-9 100k times into an AVLMap. Returns true if the size is equal to 100k
		for (int i = 1; i < 100000; i++) {
			words = words + " " + std::to_string(i % 10);
		}
		tacl::Map<unsigned int, std::string> avlMap;

		std::istringstream iss(words);
		int counter = 0;

		std::string word;
		while (std::getline(iss, word, ' ')) {
			avlMap.insert(counter, word);
			counter++;
		}

		REQUIRE(avlMap.getSize() == 100000);
	}
}