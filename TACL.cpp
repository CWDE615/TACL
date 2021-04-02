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

// include the cxxopts library available at
// https://github.com/jarro2783/cxxopts/tree/2_1
#include "cxxopts.hpp" // implicitly includes several STL containers
#include "AvlTree.hpp" // Avl tree implementation
#include "MapSet.hpp"  // map of sets for search
#include "PriorityQueue.hpp" // priority queue implementations


int main(int argc, char* argv[])
{
	cxxopts::Options menu("Text Analysis Via Command Line (TACL)", "Simple text analysis functionality via the command line");

	menu.add_options("File IO")
		("l,load_file", "Load File for Analysis", cxxopts::value<std::string>())
		("o,output_file", "Set the Name of File for Output", cxxopts::value<std::string>()->default_value("TACL.txt"))
		;
	menu.add_options("Operations")
	    ("f,word_frequency_heap","Operation set to Word Frequency through a Heap")
	    ("word_frequency_vector","Operation set to Word Frequency through a Linear Priority Queue")
	    ("search_avl","Operation set to Search with an AVL Tree")
	    ("s,search_map","Operation set to Search with an Unordered Map of Sets")
	    ("extract_avl", "Operation set to Extraction with an AVL Tree")
	    ("e,extract_map", "Operation set to Extraction with an Unordered Map of Sets")
	    ("replace_avl", "Operation set to Replacement with an AVL Tree")
	    ("r,replace_map", "Operation set to Replacement with an Unordered Map of Sets")
	    ;
	
	menu.help({ "File IO" , "Operations" });

	auto parsed = menu.parse(argc, argv);

	if (parsed.count("input") == 1)
	{
		std::string input = parsed["l"].as<std::string>();
	}
	else
	{
		std::cout << "Error: Must specify exactly one input file." << std::endl;
	}

	std::string output = parsed["o"].as<std::string>();

	// set a bool for each of the operations to false
	// in an ops vector
	const int OP_COUNT = 8;
	std::vector<bool> arr(OP_COUNT, false);
	std::vector<std::string> ops = { "word_frequency_heap", "word_frequency_vector", "search_avl", "extract_avl",
	"extract_map","replace_avl","replace_map" };
	std::unordered_map<int, std::string> op_map;
	
	for (int h = 0; h < OP_COUNT; h++)
		op_map[h] = ops[h];

	// sets the appropriate elements of the ops vector to true
	// others remain false. This method allows the user to specify multiple operations
	// at once.
	for (int i = 0; i < OP_COUNT; i++)
		if (parsed.count(op_map[i]))
			arr[i] = parsed[op_map[i]].as<bool>();

	for (int j = 0; j < OP_COUNT; j++)
	{
		if (!arr[j])
			continue;

		switch (j)
		{
		case 0:
			// wfh
			break;
		case 1:
			// wfv
			break;
		case 2:
			// savl
			break;
		case 3:
			// smap
			break;
		case 4:
			// eavl
			break;
		case 5:
			// emap
			break;
		case 6:
			// ravl
			break;
		case 7:
			//rmap
			break;
		default:
			// error? not really possible though
			break;
		}
	}

	return 0;
	
}
