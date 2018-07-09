#include "Window.h"
#include "Errors.h"
#include <iostream>

namespace Aether
{
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}


		m_SDLWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (m_SDLWindow)
		{
			std::cout << "Window Created!\n";
		}
		else if (m_SDLWindow == nullptr)
		{
			fatalError("SDL Window could not be created!");
		}
		m_Render = SDL_CreateRenderer(m_SDLWindow, -1, 0);
		if (m_Render)
		{
			SDL_SetRenderDrawColor(m_Render, 255, 0, 255, 255);
			std::cout << "Renderer Created!\n";
		}
		else if (m_Render == nullptr)
		{
			fatalError("SDL Renderer could not be created!");
		}

		m_Context = SDL_GL_CreateContext(m_SDLWindow);

		if (m_Context == nullptr)
		{
			fatalError("SDL_GL context could not be created!");
		}

		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			fatalError("Could not initialize glew!");
		}


		//Check the OpenGL Version
		std::printf("*** OpenGL Version: %s ***", glGetString(GL_VERSION));

		glClearColor(0.0f, 0.5f, 1.0f, 1.0f);

		//Set VSYNC
		SDL_GL_SetSwapInterval(0);

		//Enable Alpha Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::SwapBuffer()
	{
		SDL_GL_SwapWindow(m_SDLWindow);
	}

	void Window::CleanUp()
	{
		SDL_DestroyWindow(m_SDLWindow);
		SDL_DestroyRenderer(m_Render);

		SDL_GL_DeleteContext(m_Context);
	}
}
