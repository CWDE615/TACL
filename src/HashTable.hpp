#pragma once
#include <list>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
namespace tacl {
	class HashTable
	{

	private:

		const double MAXFACTOR = 0.5;
		std::list<std::pair<int, std::string>>* table;
		unsigned int count;
		unsigned int tableSize;

		//helpers
		double getLoadFactor(unsigned int count, unsigned int tableSize);
		unsigned int hash(int key);
		void rehash();

		std::list<std::pair<int, std::string>>* getTable();
		unsigned int maxSize();

	public:

		HashTable();
		HashTable operator=(HashTable& rhs);

		void insert(int key, std::string value);
		bool has(int key);
		std::string search(int key);
		bool remove(int key);
		int size();

	};

	//constructs the hash table with a default size of 31, and a count of 0
	HashTable::HashTable() {

		count = 0;
		tableSize = 31;


		table = new std::list<std::pair<int, std::string>>[tableSize];

	}
	//Operator overloader, fairly straight forward and self explanatory.
	HashTable HashTable::operator=(HashTable& rhs) {

		table = rhs.getTable();
		count = rhs.size();
		tableSize = rhs.maxSize();
		return *this;

	}
	//Helper function for operator overloader.
	unsigned int HashTable::maxSize() {

		return tableSize;

	}
	//Helper function for operator overloarder.
	std::list<std::pair<int, std::string>>* HashTable::getTable() {

		return table;

	}
	//Returns the current load factor of the hash table. Load factor is calculated by number of elements within the Hashtable divided by the tables size.
	double HashTable::getLoadFactor(unsigned int count, unsigned int tableSize) {

		return ((double)count) / tableSize;

	}
	//Hashes a key by dividing the key by the table size and passing back the remainder.
	unsigned int HashTable::hash(int key) {

		return key % tableSize;

	}
	//If (Load factor is >= MaxFactor) Increases the table size by times 2 plus 1 (to keep it prime), and rehashes all the keys
	void HashTable::rehash() {

		unsigned int tempSize = tableSize;
		tableSize = tableSize * 2 + 1;
		std::list <std::pair<int, std::string>>* tempArr = table;
		table = new std::list <std::pair<int, std::string>>[tableSize];

		for (unsigned int i = 0; i < tempSize; i++) { //copies old table into new table and rehashes each of the key values
			for (auto iter = tempArr[i].begin(); iter != tempArr[i].end(); iter++) {
				table[hash(iter->first)].emplace_back(iter->first, iter->second);
			}
		}

	}
	//Inserts new keys into the table
	void HashTable::insert(int key, std::string value) {

		if (!has(key)) { //if the key does not exist within the Table, create one and push back the 
			table[hash(key)].emplace_back(key, value);
		}
		else {
			return;
		}
		count++;

		if (getLoadFactor(count, tableSize) >= MAXFACTOR) {
			rehash();
		}

	}
	//Returns whether or not a key is present within the table
	bool HashTable::has(int key) {

		unsigned int hashVal = hash(key);
		for (auto finder = table[hashVal].begin(); finder != table[hashVal].end(); finder++) {
			if (finder->first == key) {
				return true;
			}
		}
		return false;

	}
	//Removes a key value pair (if present).
	bool HashTable::remove(int key) {

		int hashVal = hash(key);
		auto& newTable = table[hashVal];
		bool exists = false;

		for (auto itr = begin(newTable); itr != end(newTable); itr++) {
			if (itr->first == key) {
				exists = true;
				itr = newTable.erase(itr);
				count--;
				break;
			}
		}

		return exists;

	}
	//returns the size of the table in the form of a count integer
	int HashTable::size() {

		return count;

	}
	//Searches the table using a key, and returns a string based on the key value. Will print ERROR: Key not found if the key isn't found
	std::string HashTable::search(int key) {

		unsigned int hashVal = hash(key);
		for (auto finder = table[hashVal].begin(); finder != table[hashVal].end(); finder++) { //Loops through the table until it finds a key value pair matching the key passed in.
			if (finder->first == key) {
				return finder->second; //returns the value matching the passed in key.
			}
		}
		return "ERROR: Key Not Found!";

	}
}