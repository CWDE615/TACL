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
	
	//AVLMap Tests

	TEST_CASE("AVLMap Insert 100k Words", "[insert AVLMAP]") //tests insertion of the AVLMap
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
		//Passes if the AVLMap size is equal to 100k

	}

	TEST_CASE("AVLMap Search Value", "[insert AVLMAP][search value AVLMAP]") //tests insertion and search value of the AVLMap
	{

		std::string words = std::to_string(0); 
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

		std::vector<int> positionVector;

		for (int i = 0; i < avlMap.getSize(); ++i) {
			if (avlMap.search(i) == "1") {
				positionVector.push_back(i);
			}
		}

		REQUIRE(avlMap.getSize() == 100000);
		REQUIRE(positionVector.size() == 10000);
		//Passes if the AVLMap size is equal to 100k and positionVector size is equal to 10k

	}

	TEST_CASE("AVLMap Remove Value", "[insert AVLMAP][remove value AVLMAP]") //tests insertion and remove value of the AVLMap
	{

		std::string words = std::to_string(0); 
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

		
		int sizeBefore = avlMap.getSize();

		for (int i = 0; i < sizeBefore; ++i) {
			if (avlMap.search(i) == "1") {
				avlMap.remove(i);
			}
		}
		
		REQUIRE(avlMap.getSize() == 90000);
		//Passes if the AVLMap size is equal to 90k after removing 10k 1s.

	}

	TEST_CASE("AVLMap Replace Value", "[insert AVLMAP][insert value AVLMAP][search value AVLMAP][remove value AVLMAP]") //tests insertion and replace value of the AVLMap
	{

		std::string words = std::to_string(0);
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


		int replacedCount = 0;
		std::vector<int> posVecBefore;
		std::vector<int> posVecAfter;

		for (int i = 0; i < avlMap.getSize(); ++i) {
			if (avlMap.search(i) == "1") {
				posVecBefore.push_back(i);
			}
		}

		for (int i = 0; i < avlMap.getSize(); ++i) {
			if (avlMap.search(i) == "1") {
				avlMap.remove(i);
				avlMap.insert(i, "1 replacement string");
				++replacedCount;
			}
		}

		for (int i = 0; i < avlMap.getSize(); ++i) {
			if (avlMap.search(i) == "1 replacement string") {
				posVecAfter.push_back(i);
			}
		}

		REQUIRE(avlMap.getSize() == 100000);
		REQUIRE(replacedCount == 10000);
		REQUIRE(posVecAfter.size() == posVecBefore.size());
		//Passes if the AVLMap size is equal to 100k, replacedCount is equal to 10k, and posVecBefore and posVecAfter sizes are the same.

	}

	TEST_CASE("AVLMap Remove 100k Words", "[insert AVLMAP][remove key AVLMAP]") //tests removal of the AVLMap
	{
		std::string words = std::to_string(0); //This test inserts 0-9 100k times into an AVLMap, and then removes all 100k elements. Returns true if the size is equal to 0.
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
		for (int i = 0; i < 100000; i++) {
			avlMap.remove(i);
		}
		REQUIRE(avlMap.getSize() == 0);
		//Passes if the AVLMap size is equal to 0 (or empty)

	}

	TEST_CASE("AVLMap Search Value Remove Value Replace Value", "[insert AVLMAP][insert value AVLMAP][search value AVLMAP][remove value AVLMAP]") //tests insertion, replace value, search value of the AVLMap
	{

		std::string words = std::to_string(0);
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


		int replacedCount = 0;
		std::vector<int> posVecBefore;
		std::vector<int> posVecAfter;

		for (int i = 0; i < avlMap.getSize(); ++i) {
			if (avlMap.search(i) == "2") {
				posVecBefore.push_back(i);
			}
		}

		for (int i = 0; i < avlMap.getSize(); ++i) {
			if (avlMap.search(i) == "2") {
				avlMap.remove(i);
				avlMap.insert(i, "2 replacement string");
				++replacedCount;
			}
		}

		for (int i = 0; i < avlMap.getSize(); ++i) {
			if (avlMap.search(i) == "2 replacement string") {
				posVecAfter.push_back(i);
			}
		}

		REQUIRE(avlMap.getSize() == 100000); //Passes if the AVLMap size is equal to 100k

		int sizeBefore = avlMap.getSize();

		for (int i = 0; i < sizeBefore; ++i) {
			if (avlMap.search(i) == "1") {
				avlMap.remove(i);
			}
		}

		REQUIRE(avlMap.getSize() == 90000);
		REQUIRE(replacedCount == 10000);
		REQUIRE(posVecAfter.size() == posVecBefore.size());
		//Passes if the AVLMap size is equal to 90k, replacedCount is equal to 10k, and posVecBefore and posVecAfter sizes are the same.

	}

	//HashTable Tests

	TEST_CASE("HashTable Insert 100k Words", "[insert HashTable]") //tests insertion into HashTable
	{
		std::string words = std::to_string(0); //This test inserts 0-9 100k times into an AVLMap, and then removes all 100k elements. Returns true if the size is equal to 0.
		for (int i = 1; i < 100000; i++) {
			words = words + " " + std::to_string(i % 10);
		}
		tacl::HashTable hashedTable;

		std::istringstream iss(words);
		int counter = 0;

		std::string word;
		while (std::getline(iss, word, ' ')) {
			hashedTable.Insert(counter, word);
			counter++;
		}
		REQUIRE(hashedTable.Size() == 100000);
		//Passes if the HashTable size is equal to 100k

	}

	TEST_CASE("HashTable Remove 100k Words", "[insert HashTable][remove key HashTable]") //tests removal of the HashTable
	{
		std::string words = std::to_string(0); //This test inserts 0-9 100k times into an AVLMap, and then removes all 100k elements. Returns true if the size is equal to 0.
		for (int i = 1; i < 100000; i++) {
			words = words + " " + std::to_string(i % 10);
		}
		tacl::HashTable hashedTable;

		std::istringstream iss(words);
		int counter = 0;

		std::string word;
		while (std::getline(iss, word, ' ')) {
			hashedTable.Insert(counter, word);
			counter++;
		}
		for (int i = 0; i < 100000; i++) {
			hashedTable.RemoveKey(i);
		}
		REQUIRE(hashedTable.Size() == 0);
		//Passes if the HashTable size is 0 (or empty)

	}

	TEST_CASE("HashTable Replace 100k Words", "[insert HashTable][replace value HashTable]") //tests replacement functionality of the HashTable
	{
		std::string words = std::to_string(0); //This test inserts 0-9 100k times into an AVLMap, and then replaces all values of "1" with "1 replacement string"
		for (int i = 1; i < 100000; i++) {
			words = words + " " + std::to_string(i % 10);
		}
		tacl::HashTable hashedTable;

		std::istringstream iss(words);
		int counter = 0;

		std::string word;
		while (std::getline(iss, word, ' ')) {
			hashedTable.Insert(counter, word);
			counter++;
		}
		std::vector<int> normalVecPos = hashedTable.SearchValue("1");
	
		hashedTable.ReplaceValue("1", "1 replacement string");
		
		std::vector<int> replacedVecPos = hashedTable.SearchValue("1 replacement string");

		REQUIRE(hashedTable.Size() == 100000);
		REQUIRE(normalVecPos.size() == replacedVecPos.size());
		//Passes tests if the table size is 100k and there are the same amount of "1 replacement string" within the HashTable as there were "1"'s before the replacement.

	}

	TEST_CASE("HashTable Search Value Remove Value Replace Value", "[insert HashTable][replace value HashTable][search value HashTable][remove value HashTable]") //tests all functionality of the HashTable
	{
		std::string words = std::to_string(0); 
		for (int i = 1; i < 100000; i++) {
			words = words + " " + std::to_string(i % 10);
		}
		tacl::HashTable hashedTable;

		std::istringstream iss(words);
		int counter = 0;

		std::string word;
		while (std::getline(iss, word, ' ')) {
			hashedTable.Insert(counter, word);
			counter++;
		}
		std::vector<int> normalVecPos = hashedTable.SearchValue("2");

		hashedTable.ReplaceValue("2", "2 replacement string");

		std::vector<int> replacedVecPos = hashedTable.SearchValue("2 replacement string");

		REQUIRE(hashedTable.Size() == 100000);
		REQUIRE(normalVecPos.size() == replacedVecPos.size());
		//Passes tests if the table size is 100k and there are the same amount of "2 replacement string" within the HashTable as there were "1"'s before the replacement.

		bool removed = hashedTable.RemoveValue("2 replacement string");

		REQUIRE(removed);
		REQUIRE(hashedTable.Size() == 90000);
		//Passes tests if "2 replacement string" is successfully removed from the hash table and the table size drops down to 90k.
	}

	TEST_CASE("HashTable Remove Value", "[insert HashTable][remove value HashTable]") //tests remove value functionality of the HashTable
	{
		std::string words = std::to_string(0);
		for (int i = 1; i < 100000; i++) {
			words = words + " " + std::to_string(i % 10);
		}
		tacl::HashTable hashedTable;

		std::istringstream iss(words);
		int counter = 0;

		std::string word;
		while (std::getline(iss, word, ' ')) {
			hashedTable.Insert(counter, word);
			counter++;
		}
		
		bool removed = hashedTable.RemoveValue("2");

		REQUIRE(removed);
		REQUIRE(hashedTable.Size() == 90000);
		//Passes tests if "2 replacement string" is successfully removed from the hash table and the table size drops down to 90k.
	}

	TEST_CASE("HashTable Search Value", "[insert HashTable][search value HashTable]") //tests search functionality of the HashTable
	{
		std::string words = std::to_string(0); //This test inserts 0-9 100k times into an AVLMap, and then searches each number inside the HashTable.
		for (int i = 1; i < 100000; i++) {
			words = words + " " + std::to_string(i % 10);
		}
		tacl::HashTable hashedTable;

		std::istringstream iss(words);
		int counter = 0;

		std::string word;
		while (std::getline(iss, word, ' ')) {
			hashedTable.Insert(counter, word);
			counter++;
		}
		std::vector<int> vecPosZero = hashedTable.SearchValue("0");
		std::vector<int> vecPosOne = hashedTable.SearchValue("1");
		std::vector<int> vecPosTwo = hashedTable.SearchValue("2");
		std::vector<int> vecPosThree = hashedTable.SearchValue("3");
		std::vector<int> vecPosFour = hashedTable.SearchValue("4");
		std::vector<int> vecPosFive = hashedTable.SearchValue("5");
		std::vector<int> vecPosSix = hashedTable.SearchValue("6");
		std::vector<int> vecPosSeven = hashedTable.SearchValue("7");
		std::vector<int> vecPosEight = hashedTable.SearchValue("8");
		std::vector<int> vecPosNine = hashedTable.SearchValue("9");

		REQUIRE(vecPosZero.size() == 10000);
		REQUIRE(vecPosOne.size() == 10000);
		REQUIRE(vecPosTwo.size() == 10000);
		REQUIRE(vecPosThree.size() == 10000);
		REQUIRE(vecPosFour.size() == 10000);
		REQUIRE(vecPosFive.size() == 10000);
		REQUIRE(vecPosSix.size() == 10000);
		REQUIRE(vecPosSeven.size() == 10000);
		REQUIRE(vecPosEight.size() == 10000);
		REQUIRE(vecPosNine.size() == 10000);
		//Tests pass if each number appears 10k times.

	}

}