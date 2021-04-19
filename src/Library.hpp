#pragma once
/* MIT License

Copyright(c) 2021 Christopher William Driggers - Ellis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sub license, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include<fstream>

namespace tacl
{
    // from Christopher's submission to Project 1
    // prints ids in the passed vector reference. O(n), where n is the number of elements in the vector
    template<typename T>
    void print(std::vector<T>& data)
    {
        for (auto iter = data.begin(); iter != data.end(); iter++)
            std::cout << *iter << std::endl;
    }

    // from Christopher's submission to Project 1
    // prints the success of a function that returns a bool
    void printSuccess(bool success)
    {
        if (success)
            std::cout << "successful" << std::endl;
        else
            std::cout << "unsuccessful" << std::endl;
    }

    // from Christopher's submission to Project 1
    // gets the remainder of a line following the command's first word. substr and getline are O(s), where s is the length of the string, so this runs in
    // that time as well.
    std::string getLineRemoveSpace()
    {
        std::string line;
        std::getline(std::cin, line);
        return line.substr(1, line.size() - 1);
    }

    // creates a copy of the passed in array of any type and returns a pointer to the newly created array
    template<typename T>
    T* copy(T* arr, const unsigned int currSize, const unsigned int finalSize)
    {
        T* temp = new T[finalSize]; // Create pointer to new array

        int copyLen = ((currSize < finalSize) ? currSize : finalSize);

        for (int i = 0; i < copyLen; i++)
        {
            temp[i] = arr[i];
        }

        return temp; // return newly created array
    }

    // identifies the filename of the passed in input
    std::string getFilename(const std::string& input, std::string prefix)
    {
        return prefix + input;
    }

    // Loads the identified file known as "input" if the file is available
    std::string loadFile(const std::string& input)
    {
        std::string word;
        std::ifstream file(input);
        std::string dataString;

        if (!file.is_open()) // check that file is open
            return dataString; // returns an empty dataVector string

        while (std::getline(file, word)) // get every line of the file and add it to the string: dataVector
        {
           if (word != "")
               dataString += (" " + word);
        }

        file.close();      // close the file
        return dataString; // return the dataVector string of all  words in the file
    }

    // outputs a created file with the passed in name and its contents
    bool outputFile(const std::string& output, const std::vector<std::string> dataVector, int wordPerLine = 24)
    {
        std::ofstream file(output, std::ios_base::app);
        
        int i = 0;

        if (!file.is_open()) // if the file is not open return false that the file "output" was not correctly output
            return false;

        for (auto head = dataVector.begin(); head != dataVector.end(); head++)
        {
            file << *head << " ";
            i++;

            if (i >= wordPerLine) // proceed to a new line if the number of words exceeds 24
            {
                file << std::endl << std::endl;
                i = 0;
            }
        }

        file << std::endl;

        file.close(); // close the file
        return true; // return true if the file was correctly output
    }


}
