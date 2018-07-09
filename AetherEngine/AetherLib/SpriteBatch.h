#pragma once

#include <glew.h>
#include "Vertex.h"
#include <glm.hpp>
#include <vector>

namespace Aether
{
	enum class GlyphSortType
	{
		NONE, 
		FRONT_TO_BACK, 
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph
	{

		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;

	};

	class RenderBatch
	{
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : 
			offset(Offset), 
			numVertices(NumVertices), 
			texture(Texture)
		{

		}

		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void Init(); //1

		void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE); //2
		void End(); //4

		void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color); //DestRect (position (XY), Size(ZW))

		void DrawBatch(); //5

	private:

		void CreateRenderBatches();

		void CreateVertexArray();

		void SortGlyphs();

		static bool CompareFrontToBack(Glyph* a, Glyph* b);
		static bool CompareBackToFront(Glyph* b, Glyph* a);
		static bool CompareTexture(Glyph* a, Glyph* b);


		GLuint m_VBO;
		GLuint m_VAO;

		GlyphSortType m_SortType;

		std::vector<Glyph*> m_Glyphs;
		std::vector<RenderBatch> m_RenderBatches;

	};
}

