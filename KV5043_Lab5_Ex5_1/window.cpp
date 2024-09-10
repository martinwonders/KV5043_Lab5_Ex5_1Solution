#include "window.h"
#include <iostream>
#include <SDL.h>

Window::Window(const std::string& name, int x, int y, int width, int height)
{
	windowName = name;
	windowX = x;
	windowY = y;
	windowWidth = width;
	windowHeight = height;
	isRunning = true;
	showFrameRate = false;
	if (!Initialise())
	{
		isRunning = false;
		std::cout << "Error initialising SDL..." << std::endl;
	}
	deltaTimeMillis = static_cast<Uint16>(round((1.0f / frameRate) * 1000));
	this->frameRate = frameRate;
}

void Window::Render()
{
	///////////////////////////////////
	//Render everything here
	///////////////////////////////////
	for (Rectangle& rect : rectanglesToRender)
	{
		SDL_Rect r;
		r.x = static_cast<int>(rect.xPosition);
		r.y = static_cast<int>(rect.yPosition);
		r.w = static_cast<int>(rect.width);
		r.h = static_cast<int>(rect.height);
		SDL_SetRenderDrawColor(
			renderer, 
			rect.colour.red,
			rect.colour.blue,
			rect.colour.green,
			rect.colour.alpha
		);
		SDL_RenderFillRect(renderer, &r);
	}
}

void Window::Run()
{
	int count = 1;
	float aveFrameRate = 0.0f;
	while (isRunning)
	{
		///////////////////////////////////
		// set the frame rate
		///////////////////////////////////
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), tickCount + deltaTimeMillis)) {}
		deltaTime = (SDL_GetTicks() - tickCount) / 1000.0f;
		//This is for debugging see Game programming architecture 8.5.5
		if (deltaTime > (1.0f / frameRate) + 0.01)
		{
			deltaTime = 1.0f / frameRate;
		}
		tickCount = SDL_GetTicks();
		
		if (showFrameRate)
		{
			 
			aveFrameRate += (1.0f / deltaTime);
			count++;
			if (count >= 100)
			{
				std::cout << "frame rate = " << aveFrameRate/100 << std::endl;
				std::cout << "deltaTime = " << deltaTime << std::endl;
				showFrameRate = false;
			}
			
		}
		/////////////////////////////////////
		//Process input here
		/////////////////////////////////////
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}

		}

		//Update Here
		for (Rectangle& r : rectanglesToRender)
		{
			r.xPosition = r.xPosition + r.velocity.x * deltaTime;
			r.yPosition = r.yPosition + r.velocity.y * deltaTime;
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		Render();
		SDL_RenderPresent(renderer);
	}
}

void Window::addRectangle(Rectangle& rect)
{
	rectanglesToRender.push_back(rect);
}

Window::~Window()
{
	rectanglesToRender.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Window::Initialise()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}
	window = SDL_CreateWindow(windowName.c_str(), windowX, windowY, windowWidth, windowHeight, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
	return true;
}
