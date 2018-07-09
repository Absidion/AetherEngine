#include "SpriteBatch.h"
#include <algorithm>


namespace Aether
{
	SpriteBatch::SpriteBatch() : m_VBO(0), m_VAO(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{

	}

	void SpriteBatch::Init()
	{
		CreateVertexArray();
	}

	void SpriteBatch::Begin(GlyphSortType sortType /*GlyphSortType::Texture*/)
	{
		m_SortType = sortType;
		m_RenderBatches.clear();
		m_Glyphs.clear();
	}

	void SpriteBatch::End()
	{
		SortGlyphs();
		CreateRenderBatches();
	}

	void SpriteBatch::Draw(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint texture, float depth, const Color & color)
	{
		Glyph* newGlyph = new Glyph();
		newGlyph->texture = texture;
		newGlyph->depth = depth;
		
		newGlyph->topLeft.color = color;
		newGlyph->topLeft.SetPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->topRight.color = color;
		newGlyph->topRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.SetPosition(destRect.x , destRect.y);
		newGlyph->bottomLeft.SetUV(uvRect.x, uvRect.y);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);

		m_Glyphs.push_back(newGlyph);


	}

	void SpriteBatch::DrawBatch()
	{
		glBindVertexArray(m_VAO);

		for (int i = 0; i < m_RenderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_RenderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, m_RenderBatches[i].offset, m_RenderBatches[i].numVertices);
		}

		glBindVertexArray(m_VAO);
	}

	void SpriteBatch::CreateRenderBatches()
	{
		std::vector<Vertex> vertices;
		//Tells our vertices vector how back we think it's going to be so we can reserve some memory for it. (reserve)
		//Resize:: Sets the size of vertices to m_Glyphs.Size() * 6
		//We're then treating this like an array which is a lot faster.
		vertices.resize(m_Glyphs.size() * 6); 

		if (m_Glyphs.empty())
		{
			return;
		}

		//RenderBatch myBatch(0, 6, m_Glyphs[0]->texture);
		//m_RenderBatches.push_back(myBatch)
		//emplace_back cuts out the middle man. 
		//You won't need to create an object and then put it into the push_back. You can just put in the parameters, and the object will be created that way.
		//Since the vector has been declared for a specific type, you'll need to use the parameters for that type of course.
		//We're doing this instead because then we don't have to create an intermediate copy to just throw away the original.

		int offset = 0;
		int cv = 0; //current vertex
		m_RenderBatches.emplace_back(offset, 6, m_Glyphs[0]->texture);
		vertices[cv++] = m_Glyphs[0]->topLeft;
		vertices[cv++] = m_Glyphs[0]->bottomLeft;
		vertices[cv++] = m_Glyphs[0]->bottomRight;
		vertices[cv++] = m_Glyphs[0]->bottomRight;
		vertices[cv++] = m_Glyphs[0]->topRight;
		vertices[cv++] = m_Glyphs[0]->topLeft;
		offset += 6;

		for (int cg = 1; cg < m_Glyphs.size(); cg++)
		{
			if (m_Glyphs[cg]->texture != m_Glyphs[cg - 1]->texture)
			{
				m_RenderBatches.emplace_back(0, 6, m_Glyphs[cg]->texture);
			}
			else
			{
				m_RenderBatches.back().numVertices += 6;
			}

			vertices[cv++] = m_Glyphs[cg]->topLeft;
			vertices[cv++] = m_Glyphs[cg]->bottomLeft;
			vertices[cv++] = m_Glyphs[cg]->bottomRight;
			vertices[cv++] = m_Glyphs[cg]->bottomRight;
			vertices[cv++] = m_Glyphs[cg]->topRight;
			vertices[cv++] = m_Glyphs[cg]->topLeft;
			offset += 6;

		}

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		//Orphaning the Buffer: Tell opengl I don't want the old buffer at all. Throw it away and give me a new one.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
	}

	void SpriteBatch::CreateVertexArray()
	{
		if (m_VAO == 0)
		{
			glGenVertexArrays(1, &m_VAO);

		}
		glBindVertexArray(m_VAO);
		if (m_VBO == 0)
		{
			glGenBuffers(1, &m_VBO);

		}
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		//Positions
		glEnableVertexAttribArray(0); //Think of this as an array. Positions is the first thing in it. 0 is the index.

		glEnableVertexAttribArray(1); //Think of this as an array. Positions is the first thing in it. 0 is the index.

		glEnableVertexAttribArray(2); //Think of this as an array. Positions is the first thing in it. 0 is the index.
		
        //This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); //We're pointing opengl to the start of our data, number of elements (x,y), type of variable (float), ..., ..., ...
		//This is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//This is the uv attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}
	void SpriteBatch::SortGlyphs()
	{
		switch (m_SortType)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), CompareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), CompareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), CompareTexture);
			break;
		}
	}
	bool SpriteBatch::CompareFrontToBack(Glyph * a, Glyph * b)
	{
		return (a->depth < b->depth);
	}
	bool SpriteBatch::CompareBackToFront(Glyph * a, Glyph * b)
	{
		return (a->depth > b->depth);
	}
	bool SpriteBatch::CompareTexture(Glyph * a, Glyph * b)
	{
		return (a->texture > b->texture);
	}
}
