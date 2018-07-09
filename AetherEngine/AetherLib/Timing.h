#pragma once
#include <SDL.h>
namespace Aether
{
	class FPSLimiter
	{
	public:
		FPSLimiter();
		void Init(float targetFPS);

		void SetMaxFPS(float targetFPS);

		void Begin();
		//End will return the current FPS
		float End();
	private:
		void CalculateFPS();

		unsigned int m_StartTicks;

		float m_FPS;
		float m_frameTime;
		float m_MaxFPS;

	};


}