#ifndef FILEHANDLING_H
#define FILEHANDLING_H
#include <string>
#include <vector>

namespace fileParameters
{
	const std::string FILE_NAME = "windowParameters.txt";
	const char DELIMITER = ',';
}

namespace configParameters
{
	const std::string RECT_IDENTIFIER = "rectangle";
}

void readFromFile(const std::string& fileName);

void readFromFile(const std::string& fileName, std::string& fileContents);

void splitString(const std::string& str, char delimiter, std::vector<std::string> &result);

#endif // FILEHANDLING_H



