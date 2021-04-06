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
#include "Map.hpp" // Avl tree implementation
#include "MapSet.hpp"  // map of sets for search
#include "PriorityQueue.hpp" // priority queue implementations
#include <string>

namespace tacl
{
	std::string getFilename(const std::string& input, std::string prefix)
	{
		return prefix + input;
	}

	void wordFrequencyHeap(const std::string& input, const std::string& output)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));
	}

	void wordFrequencyVector(const std::string& input, const std::string& output)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));
	}

	void searchAvl(const std::string& input, const std::string& output)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));
	}

	void searchMap(const std::string& input, const std::string& output)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));
	}

	void extractAvl(const std::string& input, const std::string& output)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));
	}

	void extractMap(const std::string& input, const std::string& output)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));
	}

	void replaceAvl(const std::string& input, const std::string& output)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));
	}

	void replaceMap(const std::string& input, const std::string& output)
	{
		std::string fileIn(getFilename(input, "../input/"));
		std::string fileOut(getFilename(output, "../output/"));
	}
}