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

		cout << endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		istringstream iss(words);
		int counter = 0;

		string word;
		while (getline(iss, word, ' ')) {
			avlMap.insert(counter, word);
			counter++;
		}

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		cout << "AVLMap construction run time in micro seconds: " << duration.count() << endl; //prints out how long it took the function to run

	}

	void MapWrapper::searchMap(std::string value) {
		
		vector<int> positionVector;

		cout << endl; //ensures spacing between key function printing
		cout << "~~~AVLMap Search~~~" << endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		for (int i = 0; i < avlMap.getSize(); ++i) {
			if (avlMap.search(i) == value) {
				positionVector.push_back(i);
			}
		}

		cout << "Found " << positionVector.size() << " instances of \"" << value << "\" within the AVLMap! Key positions returned." << endl;

		cout << "~~~AVLMAP Search~~~" << endl;
		cout << endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		cout << "AVLMap value search run time in micro seconds: " << duration.count() << endl; //prints out how long it took the function to run

	}

	void MapWrapper::replaceMap(std::string value, std::string newValue) {

		cout << endl;//ensures spacing between key function printing
		cout << "~~~AVLMap Replace~~~" << endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		int replacedCount = 0;

		for (int i = 0; i < avlMap.getSize(); ++i) {
			if (avlMap.search(i) == value) {
				avlMap.remove(i);
				avlMap.insert(i, newValue);
				++replacedCount;
			}
		}

		cout << "Replaced " << replacedCount << " values of \"" << value << "\" with \"" << newValue << "\"." << endl;
		cout << "~~~AVLMap Replace~~~" << endl;
		cout << endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		cout << "AVLMap value replace run time in micro seconds: " << duration.count() << endl; //prints out how long it took the function to run

	}

	void MapWrapper::removeMap(std::string value) {

		cout << endl;//ensures spacing between key function printing
		cout << "~~~AVLMap Removal~~~" << endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		int sizeBefore = avlMap.getSize();

		cout << "Size of AVLMap before removal: " << sizeBefore << endl;
		cout << "Attempting to remove \"" << value << "\"." << endl;

		for (int i = 0; i < sizeBefore; ++i) {
			if (avlMap.search(i) == value) {
				avlMap.remove(i);
			}
		}

		int sizeAfter = avlMap.getSize();

		if (sizeBefore == sizeAfter) {
			cout << "ERROR: Key Not Found!" << endl;
		}
		else if (sizeBefore != sizeAfter) {
			cout << "SUCCESS: Value Pair(s) Removed!" << endl;
			cout << "Size of AVLMap after removal: " << sizeAfter << endl;
		}

		cout << "~~~AVLMap Removal~~~" << endl;
		cout << endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		cout << "AVLMap value removal run time in micro seconds: " << duration.count() << endl; //prints out how long it took the function to run

	}



}