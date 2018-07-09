#include "Game.h"
#include <string>
#include "Errors.h"


Game::Game() : 
	m_time(0.0f),
	m_MaxFPS(60.0f),
	m_ScreenWidth(800),
	m_ScreenHeight(600)
{

}

Game::~Game()
{

}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{	
	m_ScreenWidth = width;
	m_ScreenHeight = height;

	m_Window.Create("Aether Engine", m_ScreenWidth, m_ScreenHeight, 0);

	m_Camera.Init(m_ScreenWidth, m_ScreenHeight);

	isRunning = true;

	SetupShaders();

	m_SpriteBatch.Init();
	m_FPSLimiter.Init(m_MaxFPS);
}

void Game::SetupShaders()
{
	m_colorProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_colorProgram.addAttribute("vertexPosition");
	m_colorProgram.addAttribute("vertexColor");
	m_colorProgram.addAttribute("vertexUV");
	m_colorProgram.LinkShaders();
}

void Game::HandleEvents()
{
	SDL_Event evnt;

	const float CAMERA_SPEED = 2.0f; //Temp Variable
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			isRunning = false;
			m_GameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			m_InputManager.KeyPress(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_InputManager.KeyRelease(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_InputManager.KeyPress(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_InputManager.KeyRelease(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:
			m_InputManager.SetMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		default:
			break;
		}

		if(m_InputManager.isKeyPressed(SDLK_w))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec2(0.0, CAMERA_SPEED));
		else if(m_InputManager.isKeyPressed(SDLK_s))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec2(0.0, -CAMERA_SPEED));
		else if (m_InputManager.isKeyPressed(SDLK_a))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
		else if (m_InputManager.isKeyPressed(SDLK_d))
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec2(CAMERA_SPEED, 0.0));
		else if (m_InputManager.isKeyPressed(SDLK_q))
			m_Camera.SetScale(m_Camera.GetScale() + SCALE_SPEED);
		else if (m_InputManager.isKeyPressed(SDLK_e))
			m_Camera.SetScale(m_Camera.GetScale() - SCALE_SPEED);

		if (m_InputManager.isKeyPressed(SDL_BUTTON_LEFT))
		{
			glm::vec2 mouseCoords = m_InputManager.GetMouseCoords();
			mouseCoords = m_Camera.ConvertScreentoWorld(mouseCoords);
			std::cout << mouseCoords.x << ", " << mouseCoords.y << std::endl;
		}
	}


}

void Game::Update()
{
	m_Camera.Update();
}

void Game::Render()
{

	glClearDepth(1.0); //Tells opengl what depth it should clear too
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //When you draw triangles, it adds color to the screne, this clears stuff like that. This clears color and depth buffer

	m_colorProgram.UseProgram();
	glActiveTexture(GL_TEXTURE0);
	
	GLint textureLocation = m_colorProgram.GetUniformLocation("tex2D");
	glUniform1i(textureLocation, 0);

	GLint ProjectionLocation = m_colorProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = m_Camera.GetCameraMatrix();

	glUniformMatrix4fv(ProjectionLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

	glm::vec4 pos(0.0f, 0.0f, 50, 50); 
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f); 
	static Aether::GLTexture texture = Aether::ResourceManager::getTexture("Textures/PNG/CharacterRight_Standing.png");
	Aether::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	m_SpriteBatch.Begin();

	m_SpriteBatch.Draw(pos, uv, texture.id, 0.0f, color);

	m_SpriteBatch.End();
	m_SpriteBatch.DrawBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	m_colorProgram.UnuseProgram();

	m_Window.SwapBuffer();

}

void Game::Clean()
{

	SDL_Quit();

	std::cout << "Game Cleaned!\n";
}

void Game::GameLoop()
{
	Init("AetherEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (Running())
	{
		m_FPSLimiter.Begin();

		HandleEvents();
		Update();
		Render();

		m_FPS = m_FPSLimiter.End();

		static int frameCount = 0;
		frameCount++;
		if (frameCount == 10)
		{
			//std::cout << m_FPS << std::endl;
			frameCount = 0;
		}
	}
	Clean();

}