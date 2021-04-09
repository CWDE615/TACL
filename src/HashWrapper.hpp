#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include "HashTable.hpp"

namespace tacl {
	class HashWrapper {

	private:
		HashTable table;

	public:
		HashWrapper(std::string words); //constructor

		void searchHashTable(std::string value); //Search functionality

		void replaceHashTable(std::string value, std::string newValue); //Replace functionality

		void removeHashTable(std::string value); //Remove functionality

	};

	HashWrapper::HashWrapper(std::string words) {

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		std::istringstream iss(words);
		int counter = 0;

		std::string word;
		while (getline(iss, word, ' ')) {
			table.Insert(counter, word);
			counter++;
		}

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "HashTable construction run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}

	void HashWrapper::removeHashTable(std::string value) {

		std::cout << std::endl;//ensures spacing between key function printing
		std::cout << "~~~HashTable Removal~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		std::cout << "Size of HashTable before removal: " << table.Size() << std::endl;
		std::cout << "Attempting to remove \"" << value << "\"." << std::endl;

		bool removed = table.RemoveValue(value);

		if (!removed) {
			std::cout << "ERROR: Key Not Found!" << std::endl;
		}
		else if (removed) {
			std::cout << "SUCCESS: Value Pair(s) Removed!" << std::endl;
			std::cout << "Size of HashTable after removal: " << table.Size() << std::endl;
		}

		std::cout << "~~~HashTable Removal~~~" << std::endl;
		std::cout << std::endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "HashTable value removal run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}

	void HashWrapper::replaceHashTable(std::string value, std::string newValue) {

		std::cout << std::endl;//ensures spacing between key function printing
		std::cout << "~~~HashTable Replace~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		unsigned int replacedCount = table.ReplaceValue(value, newValue);

		std::cout << "Replaced " << replacedCount << " values of \"" << value << "\" with \"" << newValue << "\"." << std::endl;
		std::cout << "~~~HashTable Replace~~~" << std::endl;
		std::cout << std::endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "HashTable value replace run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}

	void HashWrapper::searchHashTable(std::string value) {

		std::cout << std::endl; //ensures spacing between key function printing
		std::cout << "~~~HashTable Search~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		std::vector<int> positionVector = table.SearchValue(value);

		std::cout << "Found " << positionVector.size() << " instances of \"" << value << "\" within the HashTable! Key positions returned." << std::endl;

		std::cout << "~~~HashTable Search~~~" << std::endl;
		std::cout << std::endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "HashTable value search run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}
}