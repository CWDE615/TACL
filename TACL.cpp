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
#include "cxxopts.hpp"; // implicitly includes several STL containers

int main(int argc, char* argv[])
{
	cxxopts::Options menu("Text Analysis Via Command Line (TACL)", "Simple text analysis functionality via the command line");

	options.add_options("File IO")
		("l,load_file", "Load File for Analysis", cxxopts::value<std::string>())
		("o,output_file", "Set the Name of File for Output", cxxopts::value<std::string>())
		;
	options.add_options("Operations")
	    ("f,word_frequency_heap","Operation set to Word Frequency through a Heap")
	    ("word_frequency_vector","Operation set to Word Frequency through a Linear Priority Queue")
	    ("search_avl","Operation set to Search with an AVL Tree")
	    ("s,search_map","Operation set to Search with an Unordered Map of Sets")
	    ("extract_avl", "Operation set to Extraction with an AVL Tree")
	    ("e,extract_map", "Operation set to Extraction with an Unordered Map of Sets")
	    ("replace_avl", "Operation set to Replacement with an AVL Tree")
	    ("r,replace_map", "Operation set to Replacement with an Unordered Map of Sets")
	    ;
	
	options.help({ "File IO" , "Operations" });

	auto parsed = options.parse()argc, argv);


}
