#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Aether
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void Init(int screenWidth, int screenHeight);

		void Update();

		glm::vec2 ConvertScreentoWorld(glm::vec2 screenCoords);

		//Setters
		void SetPosition(glm::vec2 newPosition) { m_CamPosition = newPosition; m_NeedsMatrixChange = true; }
		void SetScale(float newScale) { m_Scale = newScale; m_NeedsMatrixChange = true; }

		//Getters
		glm::vec2 GetPosition() { return m_CamPosition; }
		float GetScale() { return m_Scale; }
		glm::mat4 GetCameraMatrix() { return m_CameraMatrix; }

	private:
		int m_ScreenWidth, m_ScreenHeight; //Needed for viewport

		bool m_NeedsMatrixChange; //Means do we need to update the matrix
		float m_Scale;
		glm::vec2 m_CamPosition;
		glm::mat4 m_CameraMatrix;
		glm::mat4 m_OrthoMatrix;
	};
	
}

