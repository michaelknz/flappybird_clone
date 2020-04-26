#pragma once
#include <SDL.h>
#include <string>
#include <glew.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	~Display();
	void Swap();
	void Clean_Display(float r, float g, float b, float a);
private:
	SDL_Window* window;
	SDL_GLContext context;
};

