#pragma once
#include <SDL.h>
#include <glew.h>
#include <string>
namespace Aether
{
	enum WindowFlags
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	class Window
	{
	public:
		Window();
		~Window();

		int Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void SwapBuffer();

		void CleanUp();

		int GetScreenWidth() { return m_ScreenWidth; }
		int GetScreenHeight() { return m_ScreenHeight; }


	private:
		SDL_Window * m_SDLWindow;
		SDL_Renderer* m_Render;
		SDL_GLContext m_Context;

		int m_ScreenWidth, m_ScreenHeight;

	};
}

