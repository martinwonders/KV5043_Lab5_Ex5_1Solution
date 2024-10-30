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
			Uint8 red = static_cast<Uint8>(stoi(tokens[5]));
			Uint8 green = static_cast<Uint8>(stoi(tokens[6]));
			Uint8 blue = static_cast<Uint8>(stoi(tokens[7]));
			Uint8 alpha = static_cast<Uint8>(stoi(tokens[8]));
			Colour itemColour = { red,green,blue,alpha };
			float xVelocity = stof(tokens[9]);
			float yVelocity = stof(tokens[10]);
			Vec2D recVelocity = { xVelocity, yVelocity };
			
			Rectangle rec = { recXPos, recYPos, recWidth, recHeight, itemColour, recVelocity };
			
			window.addRectangle(rec);
			tokens.clear();
		}
	}

	window.Run();
	return 0;
}