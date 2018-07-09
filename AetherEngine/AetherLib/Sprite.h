#pragma once
#include <glew.h>
#include "Vertex.h"
#include "GLTexture.h"
#include "ResourceManager.h"
#include <string>
namespace Aether
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void Init(float x, float y, float width, float height, std::string texturePath);

		void Render();

	private:
		float m_ScreenX;
		float m_ScreenY;
		float m_Width;
		float m_Height;

		GLuint m_VBOid;

		GLTexture m_Texture;

	};
}

