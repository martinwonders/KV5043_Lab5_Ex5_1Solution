#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "window.h"
#include "filehandling.h"

int main(int argc, char* argv[])
{
	std::string fileContents;

	readFromFile(fileParameters::FILE_NAME, fileContents);

	std::stringstream sStream(fileContents);

	std::string line;
	
	std::vector<std::string> tokens;

	std::getline(sStream, line);

	splitString(line, fileParameters::DELIMITER, tokens);
	
	Window window = Window(tokens[1], stoi(tokens[2]), stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]));
	tokens.clear();

	while (std::getline(sStream, line))
	{
		splitString(line, fileParameters::DELIMITER, tokens);
		
		float recXPos, recYPos, recWidth, recHeight;

		if (tokens[0] == configParameters::RECT_IDENTIFIER)
		{
			recXPos = stof(tokens[1]);		
			recYPos = stof(tokens[2]);		
			recWidth = stof(tokens[3]);		
			recHeight = stof(tokens[4]);	
			
			Rectangle rec = { recXPos, recYPos, recWidth, recHeight };
			
			window.addRectangle(rec);
			tokens.clear();
		}
	}

	window.Run();
	return 0;
}