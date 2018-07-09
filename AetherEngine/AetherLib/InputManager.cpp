#include "InputManager.h"

namespace Aether
{
	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{

	}

	void InputManager::KeyPress(unsigned int keyID)
	{
		m_KeyMap[keyID] = true;
	}
	void InputManager::KeyRelease(unsigned int keyID)
	{
		m_KeyMap[keyID] = false;
	}

	void InputManager::SetMouseCoords(float x, float y)
	{
		m_MouseCoords.x = x;
		m_MouseCoords.y = y;
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		auto it = m_KeyMap.find(keyID);
		if (it != m_KeyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}
	}

}
