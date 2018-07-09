#include <SDL.h>
#include <glew.h>
#include <iostream>

int Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Subsystems Initialized!\n";
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Instead of having 1 window that we draw too, we instead have 2. One gets drawn too, other gets cleared. They cycle.

	return 0;
}