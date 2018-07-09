#include "Camera2D.h"

namespace Aether
{
	Camera2D::Camera2D() :
		m_NeedsMatrixChange(true), 
		m_Scale(1), 
		m_CamPosition(0, 0), 
		m_CameraMatrix(1.0f),
		m_ScreenWidth(500),
		m_ScreenHeight(500),
		m_OrthoMatrix(1.0f)
	{

	}

	Camera2D::~Camera2D()
	{

	}
	void Camera2D::Init(int screenWidth, int screenHeight)
	{
		m_ScreenWidth = screenWidth;
		m_ScreenHeight = screenHeight;

		m_OrthoMatrix = glm::ortho(0.0f, (float)m_ScreenWidth, 0.0f, (float)m_ScreenHeight);

	}
	void Camera2D::Update()
	{
		if (m_NeedsMatrixChange)
		{
			glm::vec3 translate(-m_CamPosition.x + m_ScreenWidth/2, -m_CamPosition.y + m_ScreenHeight/2, 0.0f);
			m_CameraMatrix = glm::translate(m_OrthoMatrix, translate);

			glm::vec3 scale(m_Scale, m_Scale, 0.0f);
			m_CameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_CameraMatrix;

			m_NeedsMatrixChange = false;
		}

	}
	glm::vec2 Camera2D::ConvertScreentoWorld(glm::vec2 screenCoords)
	{
		//Make it so that 0 is the center
		screenCoords -= glm::vec2(m_ScreenWidth / 2, m_ScreenHeight / 2);
		//Scale the coordinates
		screenCoords /= m_Scale;
		//Translate with the camera position
		screenCoords += m_CamPosition;

		return screenCoords;
	}
}
