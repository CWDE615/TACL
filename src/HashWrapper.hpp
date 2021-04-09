#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include "HashTable.hpp"
using namespace std;

class HashWrapper{

private:
	HashTable table;

public:
	HashWrapper(string words); //constructor

	void searchHashTable(string value); //Search functionality

	void replaceHashTable(string value, string newValue); //Replace functionality

	void removeHashTable(string value); //Remove functionality

};

HashWrapper::HashWrapper(string words) {

	using namespace std::chrono;
	auto start = high_resolution_clock::now(); //Times the function

	istringstream iss(words);
	int counter = 0;

	string word;
	while (getline(iss, word, ' ')) {
		table.Insert(counter, word);
		counter++;
	}

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "HashTable construction run time in micro seconds: " << duration.count() << endl; //prints out how long it took the function to run

}

void HashWrapper::removeHashTable(string value) {
	
	cout << endl;//ensures spacing between key function printing
	cout << "~~~HashTable Removal~~~" << endl;

	using namespace std::chrono;
	auto start = high_resolution_clock::now(); //Times the function

	cout << "Size of HashTable before removal: " << table.Size() << endl;
	cout << "Attempting to remove \"" << value << "\"." << endl;

	bool removed = table.RemoveValue(value);

	if (!removed) {
		cout << "ERROR: Key Not Found!" << endl;
	}
	else if (removed) {
		cout << "SUCCESS: Value Pair(s) Removed!" << endl;
		cout << "Size of HashTable after removal: " << table.Size() << endl;
	}

	cout << "~~~HashTable Removal~~~" << endl;
	cout << endl;

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "HashTable value removal run time in micro seconds: " << duration.count() << endl; //prints out how long it took the function to run

}

void HashWrapper::replaceHashTable(string value, string newValue) {

	cout << endl;//ensures spacing between key function printing
	cout << "~~~HashTable Replace~~~" << endl;

	using namespace std::chrono;
	auto start = high_resolution_clock::now(); //Times the function

	unsigned int replacedCount = table.ReplaceValue(value, newValue);

	cout << "Replaced " << replacedCount << " values of \"" << value << "\" with \"" << newValue << "\"." << endl;
	cout << "~~~HashTable Replace~~~" << endl;
	cout << endl;

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "HashTable value replace run time in micro seconds: " << duration.count() << endl; //prints out how long it took the function to run

}

void HashWrapper::searchHashTable(string value) {

	cout << endl; //ensures spacing between key function printing
	cout << "~~~HashTable Search~~~" << endl;

	using namespace std::chrono;
	auto start = high_resolution_clock::now(); //Times the function

	vector<int> positionVector = table.SearchValue(value);

	cout << "Found " << positionVector.size() << " instances of \"" << value << "\" within the HashTable! Key positions returned." << endl;

	cout << "~~~HashTable Search~~~" << endl;
	cout << endl;

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "HashTable value search run time in micro seconds: " << duration.count() << endl; //prints out how long it took the function to run

}