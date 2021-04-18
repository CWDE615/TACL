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

Citations:
cplusplus.com & cppreference.com were used extensively to research behaviors of the STL functions
and classes utilized throughout this project. Further, the wikis and tutorials of the cxxopts library's
repo were also referenced to learn its features' proper usage.
*/

#include <exception>
// includes the cxxopts library available at 
// https://github.com/jarro2783/cxxopts/tree/2_1
#include "includes.hpp"

int main(int argc, char* argv[])
{
	cxxopts::Options menu("TACL", "Simple text analysis functionality using the command line");

	menu.add_options("File IO")
		("l,load_file", "Load File for Analysis", cxxopts::value<std::string>())
		("o,output_file", "Set the Name of File for Output", cxxopts::value<std::string>()->default_value("TACL.txt"))
		;
	menu.add_options("Operations")
	    ("f,word_frequency_heap","Operation set to Word Frequency through a Heap")
	    ("word_frequency_pq","Operation set to Word Frequency through a Linear Priority Queue")
	    ("search_avl","Operation set to Search with an AVL Tree")
	    ("s,search_map","Operation set to Search with an Unordered Map of Sets")
	    ("extract_avl", "Operation set to Extraction with an AVL Tree")
	    ("e,extract_map", "Operation set to Extraction with an Unordered Map of Sets")
	    ("replace_avl", "Operation set to Replacement with an AVL Tree")
	    ("r,replace_map", "Operation set to Replacement with an Unordered Map of Sets")
	    ;

	menu.add_options("Arguments")
		("w,word", "Word for search/extract/replace", cxxopts::value<std::string>())
		("replacement", "Replacement for Word in replace functionality", cxxopts::value<std::string>())
		("n,number", "Number of words in frequency list", cxxopts::value<unsigned int>()->default_value("10"))
		;
	
	menu.add_options("Misc")
		("h,help", "Print Help");

	try
	{
		auto parsed = menu.parse(argc, argv);

		std::string input, output;

		if (parsed.count("h") > 0)
		{
			std::cout << menu.help({ "File IO", "Operations", "Arguments", "Misc" }) << std::endl;
			return 0;
		}

		unsigned int words = parsed["n"].as<unsigned int>();

		if (parsed.count("l") != 1 || parsed.count("o") > 1)
			throw std::invalid_argument("One input file must given and at most one output file name may be given.");

		std::cout << "here 4" << std::endl;

		input = parsed["l"].as<std::string>();
		output = parsed["o"].as<std::string>();

		if (output.substr(output.size() - 4, 4) != ".txt" || input.substr(input.size() - 4, 4) != ".txt")
			throw std::invalid_argument(".txt files only.");

		std::cout << "here 3" << std::endl;
		if (parsed.count("s") + parsed.count("search_avl") + parsed.count("e") + parsed.count("extract_avl") +
			parsed.count("r") + parsed.count("replace_avl") > 0 && (parsed.count("w") > 1 || parsed.count("w") == 0))
			throw std::invalid_argument("One word must be specified for this operation or these operations.");
		
		std::string val;
		if (parsed.count("w"))
		    val = parsed["w"].as<std::string>();

		if (parsed.count("r") + parsed.count("replace_avl") > 0 && (parsed.count("replacement") >= 1 || parsed.count("replacement") == 0))
			throw std::invalid_argument("One replacement must be specified for the original word in replacement operations.");

		std::string rep;
		if (parsed.count("replacement"))
			rep = parsed["replacement"].as<std::string>();

		std::cout << "here 2" << std::endl;
		// set a bool for each of the operations to false
		// in an ops vector
		std::vector<std::string> ops = { "word_frequency_heap", "word_frequency_pq", "search_avl", "search_map", "extract_avl",
		"extract_map","replace_avl","replace_map" };
		const int OP_COUNT = ops.size();
		std::vector<bool> arr(OP_COUNT, false);
		std::unordered_map<int, std::string> op_map;

		std::cout << "here 1" << std::endl;

		for (int h = 0; h < OP_COUNT; h++)
			op_map[h] = ops[h];

		std::cout << "here" << std::endl;
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
				tacl::wordFrequency(input, output, words, false);
				break;
			case 1:
				tacl::wordFrequency(input, output, words, true);
				break;
			case 2:
				tacl::search(input, output, val, true);
				break;
			case 3:
				tacl::search(input, output, val, false);
				break;
			case 4:
				tacl::extract(input, output, val, true);
				break;
			case 5:
				tacl::extract(input, output, val, false);
				break;
			case 6:
				tacl::replace(input, output, val, rep, true);
				break;
			case 7:
				tacl::replace(input, output, val, rep, false);
				break;
			default:
				throw std::exception();
				break;
			}
		}
	}
	catch (cxxopts::OptionParseException& o)
	{
		std::cerr << o.what() << std::endl;
	}
	catch (cxxopts::OptionException& p)
	{
		std::cerr << p.what() << std::endl;
	}
	catch (std::invalid_argument& i)
	{
		std::cerr << i.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	std::cout << "All good fam" << std::endl;

	return 0;
}
