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
#include "Library.hpp" // Library.hpp is responsible for handling the files and their contents
#include "Map.hpp" // Map.hpp contains the functionality of the Map data structure 
#include "HashMap.hpp" // HashMap.hpp contains the functionality for the HashMap data structure
#include <chrono>
#include <fstream>


namespace tacl {


	class MapWrapper {

	private:
		Map<std::string, tacl::UnorderedSet<unsigned int>> m_avlMap;
		HashMap<std::string, tacl::UnorderedSet<unsigned int>> m_hashMap;
		std::vector<std::string> m_dataVectorMap;
		std::vector<std::string> m_dataVectorHMap;
		std::string m_filename;

		void getPositions(const std::string& target, UnorderedSet<unsigned int>& positionSet, Map<std::string, UnorderedSet<unsigned int>>& map);
		void getPositions(const std::string& target, UnorderedSet<unsigned int>& positionSet, HashMap<std::string, UnorderedSet<unsigned int>>& map);
		std::string setupDS(std::string& value, UnorderedSet<unsigned int>& positionSet, bool ordered);
		void display(UnorderedSet<unsigned int>& positionSet, bool ordered, std::string word);
		void replace(UnorderedSet<unsigned int>& positionSet, bool ordered, std::string word);
		void extract(UnorderedSet<unsigned int>& positionSet, bool ordered);

	public:

		MapWrapper(std::string& words, std::string filename, bool ordered); //constructor

		bool searchMap(std::string value, bool ordered = true); //Search functionality

		bool replaceMap(std::string value, std::string newValue, bool ordered = true); //Replace functionality

		bool extractMap(std::string value, bool ordered = true); //Remove functionality

	};

	// gets the position of the passed in target string and displays the number of occurrences within the ALV map data structure
	void tacl::MapWrapper::getPositions(const std::string& target, UnorderedSet<unsigned int>& positionSet, Map<std::string, UnorderedSet<unsigned int>>& map)
	{
		try
		{
			positionSet = map.search(target);
			std::cout << "Found " << positionSet.size() << " instances of \"" << target << "\" within the AVL Map!" << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "No instances of \"" << target << "\" found." << std::endl;
		}
	}

	// gets the position of the passed in target string and displays the number of occurrences within the Hashmap data structure
	void tacl::MapWrapper::getPositions(const std::string& target, UnorderedSet<unsigned int>& positionSet, HashMap<std::string, UnorderedSet<unsigned int>>& map)
	{
		try
		{
			positionSet = map.search(target);
			std::cout << "Found " << positionSet.size() << " instances of \"" << target << "\" within the Hash Map!" << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "No instances of \"" << target << "\" found." << std::endl;
		}
	}

	// sets up the display for either the Hashmap or the AVL map
	std::string tacl::MapWrapper::setupDS(std::string& value, UnorderedSet<unsigned int>& positionSet, bool ordered)
	{
		if (ordered)
			getPositions(value, positionSet, m_avlMap);
		else
			getPositions(value, positionSet, m_hashMap);

		if (ordered)
			return "AVL Map";
		else
			return "Hash Map";

	}

	// displays the number of occurrences of the passed in word if available and their positions within the provided string file 
	void tacl::MapWrapper::display(UnorderedSet<unsigned int>& positionSet, bool ordered, std::string word)
	{
		std::ofstream file(m_filename, std::ios_base::app);

		std::vector<std::string>* stream = &m_dataVectorMap;
		
	    if (!ordered)
			stream = &m_dataVectorHMap;

		file << "Found " << positionSet.size() << " instances of " << word << " in the input file " << std::endl;

		for (unsigned int i = 0; i < stream->size(); i++)
		{
			if (positionSet.find(i))
			{
				file << "\nWord found at position: " << i << std::endl;

				int begin = i - 11;
				int end = i + 12;

				if (begin < 0)
					begin = 0;
				if (end >= stream->size())
					end = stream->size() - 1;

				for (unsigned int j = begin; j <= end; j++)
				{
					file << stream->at(j) << " ";
				}

				file << std::endl;
			}
		}

		file << std::endl;
		file.close();
	}

	// replaces a word within the provided string file and outputs the changed string file
	void MapWrapper::replace(UnorderedSet<unsigned int>& positionSet, bool ordered, std::string word)
	{
		std::vector<std::string>* stream = &m_dataVectorMap;

		if (!ordered)
			stream = &m_dataVectorHMap;

		auto begin = stream->begin();
		std::vector<unsigned int> pos = positionSet.members();

		for (auto rm = pos.begin(); rm != pos.end(); rm++)
		{
			stream->erase(begin + *rm);
			stream->insert(begin + *rm, word);
		}

		outputFile(m_filename, *stream);
	}

	inline void MapWrapper::extract(UnorderedSet<unsigned int>& positionSet, bool ordered)
	{
		std::vector<std::string>* stream = &m_dataVectorMap;

		if (!ordered)
			stream = &m_dataVectorHMap;

		auto begin = stream->begin();
		std::vector<unsigned int> pos = positionSet.members();

		for (auto rm = pos.begin(); rm != pos.end(); rm++)
		{
			stream->erase(begin + *rm);
		}

		outputFile(m_filename, *stream);
	}

	// constructor for creating an analyzing the hashmap/map data structures with the passed in file
	// provides the time for completing each action
	MapWrapper::MapWrapper(std::string& words, std::string filename, bool ordered) : m_filename(filename)
	{
		std::cout << std::endl;

		if (ordered)
		{
			using namespace std::chrono;
			auto start = high_resolution_clock::now(); //Times the function

			getStringData(words, m_dataVectorMap, m_avlMap);

			auto end = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(end - start);
			std::cout << "AVLMap initialization run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run
		}
		else
		{
			using namespace std::chrono;
			auto start2 = high_resolution_clock::now(); //Times the function

			getStringData(words, m_dataVectorHMap, m_hashMap);

			auto end2 = high_resolution_clock::now();
			auto duration2 = duration_cast<microseconds>(end2 - start2);
			std::cout << "HashMap initialization run time in micro seconds: " << duration2.count() << std::endl; //prints out how long it took the function to run

		}
	}

	// analyzing the search freature functionality of the hashmap/map data structures with the passed in file
	// provides the time for completing each action
	// returns true if successful
	bool MapWrapper::searchMap(std::string value, bool ordered) 
	{
		std::cout << std::endl; //ensures spacing between key function printing
		std::cout << "~~~ Search ~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function
		UnorderedSet<unsigned int> positionSet;

		std::string ds = setupDS(value, positionSet, ordered);
		display(positionSet, ordered, value);

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);

		std::cout << "~~~ Search ~~~" << std::endl;
		std::cout << std::endl;
		std::cout << ds << " word search run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

		return true;
	}
	
	// analyzing the replacement feature functionality of the hashmap/map data structures with the passed in file
	// provides the time for completing each action
	// returns true if successful
	bool MapWrapper::replaceMap(std::string value, std::string newValue, bool ordered) 
	{

		std::cout << std::endl;//ensures spacing between key function printing
		std::cout << "~~~ Replace ~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		UnorderedSet<unsigned int> positionSet;

		std::string ds = setupDS(value, positionSet, ordered);
		replace(positionSet, ordered, newValue);

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);

		std::cout << "Replaced " << positionSet.size() << " instances of \"" << value << "\" in the " << ds << " with \"" << newValue << ".\"" << std::endl;
		std::cout << "~~~ Replace ~~~" << std::endl;
		std::cout << std::endl;

		std::cout << ds << " value replacement run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

		return true;
	}

	// analyzing the extraction feature functionality of the hashmap/map data structures with the passed in file
	// provides the time for completing each action
	// returns true if successful
	bool MapWrapper::extractMap(std::string value, bool ordered)
	{

		std::cout << std::endl; //ensures spacing between key function printing
		std::cout << "~~~ Extract ~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		UnorderedSet<unsigned int> positionSet;

		std::string ds = setupDS(value, positionSet, ordered);
		extract(positionSet, ordered);

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);

		std::cout << "Extracted " << positionSet.size() << " instances values of \"" << value << ".\"" << std::endl;
		std::cout << "~~~ Extract ~~~" << std::endl;
		std::cout << std::endl;
		std::cout << ds << " word extraction run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run
		
		return true;
	}
}