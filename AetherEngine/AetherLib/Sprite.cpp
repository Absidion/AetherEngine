#include "Sprite.h"

#include <cstddef>
namespace Aether
{
	Sprite::Sprite()
	{
		m_VBOid = 0;

	}

	Sprite::~Sprite()
	{

		if (m_VBOid != 0)
		{
			glDeleteBuffers(1, &m_VBOid);
		}

	}

	void Sprite::Init(float x, float y, float width, float height, std::string texturePath)
	{
		m_ScreenX = x;
		m_ScreenY = y;
		m_Width = width;
		m_Height = height;

		m_Texture = ResourceManager::getTexture(texturePath);

		//Generate the buffer
		if (m_VBOid == 0)
		{
			glGenBuffers(1, &m_VBOid); //Number of buffers, VBO as a reference. Generates the VBO and changes the ID of that buffer. 
		}

		//Create space for vertices using X, Y, Width, Height
		Vertex vertexData[6];

		//First Triangle
		vertexData[0].SetPosition(x + width, y + height);
		vertexData[0].SetUV(1.0f, 1.0f);

		vertexData[1].SetPosition(x, y + height);
		vertexData[1].SetUV(0.0f, 1.0f);

		vertexData[2].SetPosition(x, y);
		vertexData[2].SetUV(0.0f, 0.0f);

		vertexData[3] = vertexData[2];

		vertexData[4].SetPosition(x + width, y);
		vertexData[4].SetUV(1.0f, 0.0f);

		vertexData[5] = vertexData[0];

		for (int i = 0; i < 6; i++)
		{
			vertexData[i].color.r = 255;
			vertexData[i].color.g = 0;
			vertexData[i].color.b = 123;
			vertexData[i].color.r = 255;

		}

		vertexData[1].SetColor(0, 0, 255, 255);
		vertexData[4].SetColor(0, 255, 0, 255);





		glBindBuffer(GL_ARRAY_BUFFER, m_VBOid); //Tells opengl we want this buffer to be active

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW); //target: type of buffer, size of data, what is the data, how we're going to use it

		glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbinds the buffer. 0 indicates no buffer.

	}

	void Sprite::Render()
	{

		glBindTexture(GL_TEXTURE_2D, m_Texture.id);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBOid);

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

		glDrawArrays(GL_TRIANGLES, 0, 6); //Drawing mode, starting point, how many times we draw a vertex

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
