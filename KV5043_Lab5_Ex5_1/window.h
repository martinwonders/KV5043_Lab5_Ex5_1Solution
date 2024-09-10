#pragma once
#include <SDL.h>
#include <string>
#include <vector>

struct Vec2D
{
	float x;
	float y;
};

struct Colour
{
	Uint8 red;
	Uint8 green;
	Uint8 blue;
	Uint8 alpha;
};

struct Rectangle
{
	float xPosition;
	float yPosition;
	float width;
	float height;
	Colour colour{ 0,255,0,255 };
	Vec2D velocity{ 0.0f ,0.0f };
};



class Window
{
public:
	Window(const std::string& name, int x, int y, int width, int height);
	void Run();
	void addRectangle(Rectangle& rect);
	bool showFrameRate;
	~Window();
	
private:
	bool Initialise();
	void Render();
	bool isRunning;
	Uint32 tickCount;
	Uint16 frameRate;
	float deltaTime;
	Uint16 deltaTimeMillis;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int windowX;
	int windowY;
	int windowWidth;
	int windowHeight;
	std::string windowName;
	std::vector<Rectangle> rectanglesToRender;
};