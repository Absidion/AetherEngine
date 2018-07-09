#pragma once
#include "TextureCache.h"
#include "GLTexture.h"
#include <string>

namespace Aether
{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);

	private:
		static TextureCache m_TextureCache;
	};
}
