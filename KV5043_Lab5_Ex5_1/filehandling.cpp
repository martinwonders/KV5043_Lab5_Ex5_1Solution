#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void readFromFile(const std::string& fileName)
{
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: " << fileName << " could not be opened." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::cout << line << std::endl;
    }

    inputFile.close();
}



void readFromFile(const std::string& fileName, std::string& fileContents)
{
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: " << fileName << " could not be opened." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        fileContents += line + '\n';
    }

    inputFile.close();
}

void splitString(const std::string& str, char delimiter, std::vector<std::string> &result)
{
    std::stringstream sStream(str);
    std::string token;
    while (std::getline(sStream, token, delimiter))
    {
        result.push_back(token);
    }
}