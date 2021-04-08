#pragma once
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

class HashTable
{

private:

	const double MAXFACTOR = 0.5;
	list<pair<int, string>>* table;
	unsigned int count;
	unsigned int tableSize;

	//helpers
	double GetLoadFactor(unsigned int count, unsigned int tableSize);
	unsigned int Hash(int key);
	void Rehash();

	list<pair<int, string>>* GetTable();
	unsigned int GetCount();
	unsigned int GetTableSize();

public:
	
	HashTable();
	HashTable operator=(HashTable& rhs); 
	
	void Insert(int key, string value);
	bool HasKey(int key);
	bool HasValue(string value);
	vector<int> SearchValue(string value);
	string SearchKey(int key);
	void RemoveKey(int key);
	void RemoveValue(string value);
	void ReplaceValue(string value, string newValue);
	int Size();

};

//constructs the hash table with a default size of 31, and a count of 0
HashTable::HashTable() {

	count = 0;
	tableSize = 31;


	table = new list<pair<int, string>>[tableSize];

}
//Operator overloader, fairly straight forward and self explanatory.
HashTable HashTable::operator=(HashTable& rhs) {

	table = rhs.GetTable();
	count = rhs.GetCount();
	tableSize = rhs.GetTableSize();
	return *this;

}
//Helper function for operator overloader.
unsigned int HashTable::GetTableSize() {

	return tableSize;

}
//Helper function for operator overloarder.
unsigned int HashTable::GetCount() {

	return count;

}
//Helper function for operator overloarder.
list<pair<int, string>>* HashTable::GetTable() {

	return table;

}
//Returns the current load factor of the hash table. Load factor is calculated by number of elements within the Hashtable divided by the tables size.
double HashTable::GetLoadFactor(unsigned int count, unsigned int tableSize) {

	return ((double)count) / tableSize;

}
//Hashes a key by dividing the key by the table size and passing back the remainder.
unsigned int HashTable::Hash(int key) {

	return key % tableSize;

}
//If (Load factor is >= MaxFactor) Increases the table size by times 2 plus 1 (to keep it prime), and rehashes all the keys
void HashTable::Rehash() {

	unsigned int tempSize = tableSize;
	tableSize = tableSize * 2 + 1;
	list <pair<int, string>>* tempArr = table;
	table = new list <pair<int, string>>[tableSize];

	for (unsigned int i = 0; i < tempSize; i++) { //copies old table into new table and rehashes each of the key values
		for (auto iter = tempArr[i].begin(); iter != tempArr[i].end(); iter++) {
			table[Hash(iter->first)].emplace_back(iter->first, iter->second);
		}
	}

}
//Inserts new keys into the table
void HashTable::Insert(int key, string value) {

	if (!HasKey(key)) { //if the key does not exist within the Table, create one and push back the 
		table[Hash(key)].emplace_back(key, value);
	}
	else {
		return;
	}
	count++;

	if (GetLoadFactor(count, tableSize) >= MAXFACTOR) {
		Rehash();
	}

}
//Returns whether or not a key is present within the table
bool HashTable::HasKey(int key) {

	unsigned int hashVal = Hash(key);
	for (auto finder = table[hashVal].begin(); finder != table[hashVal].end(); finder++) {
		if (finder->first == key) {
			return true;
		}
	}
	return false;

}
//Returns whether or not a value is present within the table
bool HashTable::HasValue(string value) {

	for (int i = 0; i < tableSize; ++i) {
		unsigned int hashVal = Hash(i);
		for (auto finder = table[hashVal].begin(); finder != table[hashVal].end(); finder++) {
			if (finder->second == value) {
				return true;
			}
		}
	}
	return false;
}
//Removes a key value pair (if present).
void HashTable::RemoveKey(int key) {

	int hashVal = Hash(key);
	auto& newTable = table[hashVal];
	bool exists = false;

	for (auto itr = begin(newTable); itr != end(newTable); itr++) { 
		if (itr->first == key) {
			exists = true;
			itr = newTable.erase(itr);
			cout << "SUCCESS: Key Pair Removed!" << endl;
			count--;
			break;
		}
	}

	if (!exists) {
		cout << "ERROR: Key Not Found!" << endl;
	}

}
//returns the size of the table in the form of a count integer
int HashTable::Size() {

	return count;

}
//Searches the table using a key, and returns a string based on the key value. Will print ERROR: Key not found if the key isn't found
string HashTable::SearchKey(int key) {

	unsigned int hashVal = Hash(key);
	for (auto finder = table[hashVal].begin(); finder != table[hashVal].end(); finder++) { //Loops through the table until it finds a key value pair matching the key passed in.
		if (finder->first == key) {
			return finder->second; //returns the value matching the passed in key.
		}
	}
	return "ERROR: Key Not Found!";

}
//Searches the table using a value. As there are more than likely multiple keys containing the same value it returns a vector of keys (which are the positions of the words).
vector<int> HashTable::SearchValue(string value) {

	cout << endl; //ensures spacing between key function printing
	cout << "~~~HashTable Search~~~" << endl;

	using namespace std::chrono;
	auto start = high_resolution_clock::now(); //Times the function

	vector<int> positionVector; //Loops through the table until the end of the table. As it goes along it constructs a vector of positions (keys) where the value is found.
	for (int i = 0; i < tableSize; ++i) {
		unsigned int hashVal = Hash(i);
		for (auto finder = table[hashVal].begin(); finder != table[hashVal].end(); finder++) {
			if (finder->second == value) {
				positionVector.push_back(finder->first);
			}
		}
	}

	cout << "Found " << positionVector.size() << " instances of \"" << value << "\" within the HashTable! Key positions returned." << endl;

	cout << "~~~HashTable Search~~~" << endl;
	cout << endl;

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "HashTable value search run time in micro seconds: " << duration.count() << endl; //prints out how long it took the function to run

	return positionVector;

}
//Removes the values from the table, along with their keys.
void HashTable::RemoveValue(string value) {
	
	cout << endl;//ensures spacing between key function printing
	cout << "~~~HashTable Removal~~~" << endl;

	using namespace std::chrono;
	auto start = high_resolution_clock::now(); //Times the function

	bool exists = false;

	cout << "Size of HashTable before removal: " << Size() << endl;
	cout << "Attempting to remove \"" << value << "\"." << endl;

	for (int i = 0; i < tableSize; ++i) { //Loops through the table and searches for the passed in value. When it finds the value it removes the element from the table.
		int hashVal = Hash(i);
		auto& newTable = table[hashVal];

		for (auto itr = begin(newTable); itr != end(newTable); itr++) {
			if (itr->second == value) {
				exists = true;
				itr = newTable.erase(itr);
				count--;
				break;
			}
		}
	}
	if (HasValue(value)) { 
		RemoveValue(value);
	}
	if (!exists) {
		cout << "ERROR: Key Not Found!" << endl;
	}
	else if(exists) {
		cout << "SUCCESS: Value Pair(s) Removed!" << endl;
		cout << "Size of HashTable after removal: " << Size() << endl;
	}

	cout << "~~~HashTable Removal~~~" << endl;
	cout << endl;

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "HashTable value removal run time in micro seconds: " << duration.count() << endl; //prints out how long it took the function to run

}
//Replaces the passed in value within the table with a new passed in value.
void HashTable::ReplaceValue(string value, string newValue) {

	cout << endl;//ensures spacing between key function printing
	cout << "~~~HashTable Replace~~~" << endl;

	using namespace std::chrono;
	auto start = high_resolution_clock::now(); //Times the function

	unsigned int replacedCount = 0;

	for (int i = 0; i < tableSize; ++i) { //Loops through the entire table and replaces each value it finds matching the passed in value with newValue.
		unsigned int hashVal = Hash(i);
		for (auto finder = table[hashVal].begin(); finder != table[hashVal].end(); finder++) { 
			if (finder->second == value) { //if the second value within the pair (the string value or word) is equivalent to the passed in value then replace.
				finder->second = newValue;
				++replacedCount;
			}
		}
	}
	cout << "Replaced " << replacedCount << " values of \"" << value << "\" with \"" << newValue << "\"." << endl;
	cout << "~~~HashTable Replace~~~" << endl;
	cout << endl;

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "HashTable value replace run time in micro seconds: " << duration.count() << endl; //prints out how long it took the function to run

}