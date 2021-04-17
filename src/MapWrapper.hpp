#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Library.hpp"
#include "Map.hpp"
#include "HashMap.hpp"
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

		MapWrapper(std::string& words, std::string filename); //constructor

		bool searchMap(std::string value, bool ordered = true); //Search functionality

		bool replaceMap(std::string value, std::string newValue, bool ordered = true); //Replace functionality

		bool extractMap(std::string value, bool ordered = true); //Remove functionality

	};

	void tacl::MapWrapper::getPositions(const std::string& target, UnorderedSet<unsigned int>& positionSet, Map<std::string, UnorderedSet<unsigned int>>& map)
	{
		try
		{
			positionSet = map.search(target);
			std::cout << "Found " << positionSet.size() << " instances of \"" << target << "\" within the AVLMap!" << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "No instances of \"" << target << "\" found." << std::endl;
		}
	}

	void tacl::MapWrapper::getPositions(const std::string& target, UnorderedSet<unsigned int>& positionSet, HashMap<std::string, UnorderedSet<unsigned int>>& map)
	{
		try
		{
			positionSet = map.search(target);
			std::cout << "Found " << positionSet.size() << " instances of \"" << target << "\" within the AVLMap!" << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << "No instances of \"" << target << "\" found." << std::endl;
		}
	}

	std::string tacl::MapWrapper::setupDS(std::string& value, UnorderedSet<unsigned int>& positionSet, bool ordered)
	{
		if (ordered)
			getPositions(value, positionSet, m_avlMap);
		else
			getPositions(value, positionSet, m_hashMap);

		if (ordered)
			return "AVL map";
		else
			return "Hash map";

	}

	void tacl::MapWrapper::display(UnorderedSet<unsigned int>& positionSet, bool ordered, std::string word)
	{
		std::ofstream file(m_filename);

		std::vector<std::string>* stream = &m_dataVectorMap;
		
	    if (ordered)
			stream = &m_dataVectorHMap;

		file << "Found " << positionSet.size() << " instances of " << word << " in the file " << m_filename << std::endl;

		for (unsigned int i = 0; i < stream->size(); i++)
		{
			if (positionSet.find(i))
			{
				file << "Word found at position: " << i << std::endl;

				int begin = i - 20;
				int end = i + 20;

				if (begin < 0)
					begin = 0;
				if (end >= stream->size())
					end = stream->size() - 1;

				for (unsigned int j = begin; j <= end; j++)
				{
					file << stream->at(i) << " ";
				}

				file << std::endl;
			}
		}

		file.close();
	}

	void MapWrapper::replace(UnorderedSet<unsigned int>& positionSet, bool ordered, std::string word)
	{
		std::vector<std::string>* stream = &m_dataVectorMap;

		if (ordered)
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

		if (ordered)
			stream = &m_dataVectorHMap;

		auto begin = stream->begin();
		std::vector<unsigned int> pos = positionSet.members();

		for (auto rm = pos.begin(); rm != pos.end(); rm++)
		{
			stream->erase(begin + *rm);
		}

		outputFile(m_filename, *stream);
	}

	MapWrapper::MapWrapper(std::string& words, std::string filename) : m_filename(filename)
	{
		std::cout << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		getStringData(words, m_dataVectorMap, m_avlMap);

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "AVLMap initialization run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

		std::cout << std::endl;

		using namespace std::chrono;
		auto start2 = high_resolution_clock::now(); //Times the function

		getStringData(words, m_dataVectorHMap, m_hashMap);

		auto end2 = high_resolution_clock::now();
		auto duration2 = duration_cast<microseconds>(end2 - start2);
		std::cout << "HashMap initialization run time in micro seconds: " << duration2.count() << std::endl; //prints out how long it took the function to run

	}

	bool MapWrapper::searchMap(std::string value, bool ordered) 
	{
		std::cout << std::endl; //ensures spacing between key function printing
		std::cout << "~~~ Search ~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function
		UnorderedSet<unsigned int> positionSet;

		std::string ds = setupDS(value, positionSet, ordered);
		display(positionSet, ordered, value);
		
		std::cout << "~~~ Search ~~~" << std::endl;
		std::cout << std::endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << ds << " search run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}

	bool MapWrapper::replaceMap(std::string value, std::string newValue, bool ordered) 
	{

		std::cout << std::endl;//ensures spacing between key function printing
		std::cout << "~~~ Replace ~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		int replacedCount = 0;
		UnorderedSet<unsigned int> positionSet;

		std::string ds = setupDS(value, positionSet, ordered);
		replace(positionSet, ordered, newValue);

		std::cout << "Replaced " << replacedCount << " values of \"" << value << "\" in the " << ds << " with \"" << newValue << "\"." << std::endl;
		std::cout << "~~~ Replace ~~~" << std::endl;
		std::cout << std::endl;

		

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << ds << " value replace run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}

	bool MapWrapper::extractMap(std::string value, bool ordered)
	{

		std::cout << std::endl;//ensures spacing between key function printing
		std::cout << "~~~ Extract ~~~" << std::endl;

		using namespace std::chrono;
		auto start = high_resolution_clock::now(); //Times the function

		UnorderedSet<unsigned int> positionSet;

		std::string ds = setupDS(value, positionSet, ordered);
		extract(positionSet, ordered);

		// TODO	extraction

		std::cout << "~~~ Extract ~~~" << std::endl;
		std::cout << std::endl;

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(end - start);
		std::cout << "AVLMap value removal run time in micro seconds: " << duration.count() << std::endl; //prints out how long it took the function to run

	}
}