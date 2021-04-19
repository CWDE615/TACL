#pragma once
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

    template<typename T>
    T* copy(T* arr, const unsigned int currSize, const unsigned int finalSize)
    {
        T* temp = new T[finalSize];

        int copyLen = ((currSize < finalSize) ? currSize : finalSize);

        for (int i = 0; i < copyLen; i++)
        {
            temp[i] = arr[i];
        }

        return temp;
    }

    std::string getFilename(const std::string& input, std::string prefix)
    {
        return prefix + input;
    }

    std::string loadFile(const std::string& input)
    {
        std::string word;
        std::ifstream file(input);
        std::string dataString;

        if (!file.is_open()) // check that file is open
            return dataString;

        while (std::getline(file, word))
        {
           if (word != "")
               dataString += (" " + word);
        }

        file.close();      // close the file
        return dataString;
    }

    bool outputFile(const std::string& output, const std::vector<std::string> dataVector, int wordPerLine = 24)
    {
        std::ofstream file(output, std::ios_base::app);
        
        int i = 0;

        if (!file.is_open())
            return false;

        for (auto head = dataVector.begin(); head != dataVector.end(); head++)
        {
            file << *head << " ";
            i++;

            if (i >= wordPerLine)
            {
                file << std::endl << std::endl;
                i = 0;
            }
        }

        file << std::endl;

        file.close();
        return true;
    }


}
