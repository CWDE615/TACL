#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Map.hpp"
#include <chrono>
#include <sstream>


namespace tacl {


	class MapWrapper {

	private:
		Map<unsigned int, std::string> avlMap;

	public:

		MapWrapper(std::string words); //constructor

		void searchMap(std::string value); //Search functionality

		void replaceMap(std::string value, std::string newValue); //Replace functionality

		void removeMap(std::string value); //Remove functionality

	};


	MapWrapper::MapWrapper(std::string words) {

		std::cout << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		std::istringstream iss(words);
		int counter = 0;

		std::string word;
		while (std::getline(iss, word, ' ')) {
			avlMap.insert(counter, word);
			counter++;
		}

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "AVLMap construction run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}

	void MapWrapper::searchMap(std::string value) {
		
		std::vector<int> positionVector;

		std::cout << std::endl; //ensures spacing between key function printing
		std::cout << "~~~AVLMap Search~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		for (int i = 0; i < avlMap.size(); ++i) {
			if (avlMap.search(i) == value) {
				positionVector.push_back(i);
			}
		}

		std::cout << "Found " << positionVector.size() << " instances of \"" << value << "\" within the AVLMap! Key positions returned." << std::endl;

		std::cout << "~~~AVLMAP Search~~~" << std::endl;
		std::cout << std::endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "AVLMap value search run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}

	void MapWrapper::replaceMap(std::string value, std::string newValue) {

		std::cout << std::endl;//ensures spacing between key function printing
		std::cout << "~~~AVLMap Replace~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		int replacedCount = 0;

		for (int i = 0; i < avlMap.size(); ++i) {
			if (avlMap.search(i) == value) {
				avlMap.remove(i);
				avlMap.insert(i, newValue);
				++replacedCount;
			}
		}

		std::cout << "Replaced " << replacedCount << " values of \"" << value << "\" with \"" << newValue << "\"." << std::endl;
		std::cout << "~~~AVLMap Replace~~~" << std::endl;
		std::cout << std::endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "AVLMap value replace run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}

	void MapWrapper::removeMap(std::string value) {

		std::cout << std::endl;//ensures spacing between key function printing
		std::cout << "~~~AVLMap Removal~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		int sizeBefore = avlMap.size();

		std::cout << "Size of AVLMap before removal: " << sizeBefore << std::endl;
		std::cout << "Attempting to remove \"" << value << "\"." << std::endl;

		for (int i = 0; i < sizeBefore; ++i) {
			if (avlMap.search(i) == value) {
				avlMap.remove(i);
			}
		}

		int sizeAfter = avlMap.size();

		if (sizeBefore == sizeAfter) {
			std::cout << "ERROR: Key Not Found!" << std::endl;
		}
		else if (sizeBefore != sizeAfter) {
			std::cout << "SUCCESS: Value Pair(s) Removed!" << std::endl;
			std::cout << "Size of AVLMap after removal: " << sizeAfter << std::endl;
		}

		std::cout << "~~~AVLMap Removal~~~" << std::endl;
		std::cout << std::endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "AVLMap value removal run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}



}