#pragma once

#include <glm.hpp>

class Bullet
{
public:
	Bullet();
	~Bullet();
private:
	float m_Speed;
	glm::vec2 m_Direction;
};

