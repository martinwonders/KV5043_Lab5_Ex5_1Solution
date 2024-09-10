#include <iostream>
#include <fstream>
#include <sstream>
#include "window.h"
#include "filehandling.h"

int main(int argc, char* argv[])
{
	std::string fileContents;

	readFromFile(fileParameters::FILE_NAME, fileContents);

	std::stringstream sStream(fileContents);

	std::string line;
	
	std::string tokens[6];

	std::getline(sStream, line);

	splitString(line, fileParameters::DELIMITER, tokens, 6);

	Window window = Window(tokens[1], stoi(tokens[2]), stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]));

	while (std::getline(sStream, line))
	{
		splitString(line, fileParameters::DELIMITER, tokens, 5);
		
		float recXPos, recYPos, recWidth, recHeight;

		if (tokens[0] == configParameters::RECT_IDENTIFIER)
		{
			recXPos = stof(tokens[1]);		
			recYPos = stof(tokens[2]);		
			recWidth = stof(tokens[3]);		
			recHeight = stof(tokens[4]);	
			
			Rectangle rec = { recXPos, recYPos, recWidth, recHeight };

			window.addRectangle(rec);
		}
	}

	window.Run();
	return 0;
}