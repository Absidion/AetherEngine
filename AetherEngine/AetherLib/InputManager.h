#pragma once
#include <glm.hpp>
#include <unordered_map>
namespace Aether
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void KeyPress(unsigned int keyID);
		void KeyRelease(unsigned int keyID);

		bool isKeyPressed(unsigned int keyID);

		void SetMouseCoords(float x, float y);

		//Getters
		glm::vec2 GetMouseCoords() const { return m_MouseCoords; }
	private:
		std::unordered_map<unsigned int, bool> m_KeyMap;

		glm::vec2 m_MouseCoords;
	};
}

