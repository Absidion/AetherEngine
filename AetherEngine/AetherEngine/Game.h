#pragma once

#include <SDL.h>
#include <glew.h>
#include <AetherLib.h>
#include <GLSLProgram.h>
#include <GLTexture.h>
#include <iostream>
#include <Sprite.h>
#include <vector>
#include <Window.h>
#include <Camera2D.h>
#include <SpriteBatch.h>
#include <ResourceManager.h>
#include <InputManager.h>
#include <Timing.h>
#include <glm.hpp>

enum class GameState {PLAY, EXIT};

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void SetupShaders();

	void HandleEvents();

	void Update();

	void Render();

	void Clean();

	void GameLoop();

	bool Running() { return isRunning; }

private:
	bool isRunning;

	Aether::Window m_Window;

	GameState m_GameState;

	Aether::GLSLProgram m_colorProgram;
	Aether::Camera2D m_Camera;
	Aether::SpriteBatch m_SpriteBatch;
	Aether::InputManager m_InputManager;
	Aether::FPSLimiter m_FPSLimiter;

	int m_ScreenWidth;
	int m_ScreenHeight;

	float m_FPS;
	float m_MaxFPS;

	GLfloat m_time;
};

