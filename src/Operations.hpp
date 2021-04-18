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

#pragma once
#include "Library.hpp"
#include "MapWrapper.hpp"
#include "HeapWrapper.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace tacl
{
	void wordFrequency(const std::string& input, const std::string& output, unsigned int number, bool pq)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));

		std::string temp = loadFile(fileIn);
		tacl::HeapWrapper wrap(temp,fileOut,pq);

		std::cout << "Finding the top " << number << " most frequent words in " << input << std::endl;
		if (wrap.mostFrequentWords(number, pq))
		{
			std::cout << "Words found successfully. Check the file " << output << "." << std::endl;
		}
		else
		{
			std::cout << "Error in finding the frequencies. Check inputs and filenames." << std::endl;
		}
	}

	void search(const std::string& input, const std::string& output, std::string word, bool avl)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));

		std::string temp = loadFile(fileIn);
		tacl::MapWrapper wrap(temp, fileOut, avl);

		std::cout << "Searching for instances of " << word << " in the file " << input << std::endl;
		if (!wrap.searchMap(word, avl))
		{
			std::cout << "Error in searching for " << word << ". Check the file " << output << ".";
		}
	}

	void extract(const std::string& input, const std::string& output, std::string word, bool avl)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));

		std::string temp = loadFile(fileIn);
		tacl::MapWrapper wrap(temp, fileOut, avl);

		std::cout << "Extracting all instances of " << word << " in the file " << input << std::endl;
		if (!wrap.extractMap(word, avl))
		{
			std::cout << "Error extracting " << word << ". Check the file " << output << ".";
		}
	}

	void replace(const std::string& input, const std::string& output, std::string curr, std::string rep, bool avl)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));

		std::string temp = loadFile(fileIn);
		tacl::MapWrapper wrap(temp, fileOut, avl);

		std::cout << "Replacing all instances of " << curr << " in the file " << input << " with " << rep << std::endl;
		if (!wrap.replaceMap(curr, rep, avl))
		{
			std::cout << "Error replacing " << curr << ". Check the file " << output << ".";
		}
	}
}