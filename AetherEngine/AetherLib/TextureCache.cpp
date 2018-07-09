#include "TextureCache.h"

namespace Aether
{

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//look up the texture and see if its in the map
		auto mapIT = m_TextureMap.find(texturePath); //std::map<std::string, GLTexture>::iterator mit = m_TextureMap.find()

		//check if its not in the map
		if (mapIT == m_TextureMap.end())
		{
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//make_pair does what the comment below does. It auto identifies the types based on what you input:
			//std::pair<std::string, GLTexture> newPair(texturePath, newTexture);

			m_TextureMap.insert(make_pair(texturePath, newTexture));

			std::cout << "Loaded Cached Texture!\n";

			return newTexture;
		}

		std::cout << "Loaded Texture!\n";
		return mapIT->second;
	}
}
