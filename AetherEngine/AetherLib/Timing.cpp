#include "Timing.h"

namespace Aether
{

	FPSLimiter::FPSLimiter()
	{

	}

	void FPSLimiter::Init(float targetFPS)
	{
		SetMaxFPS(targetFPS);
	}

	void FPSLimiter::SetMaxFPS(float targetFPS)
	{
		m_MaxFPS = targetFPS;
	}

	void FPSLimiter::Begin()
	{
		m_StartTicks = SDL_GetTicks();
	}

	float FPSLimiter::End()
	{
		CalculateFPS();

		float frameTicks = SDL_GetTicks() - m_StartTicks;
		if (1000.0f / m_MaxFPS > frameTicks)
		{
			SDL_Delay(1000.0f / 60.0f - frameTicks);
		}

		return m_FPS;
	}

	void FPSLimiter::CalculateFPS()
	{

		static const int NUM_SAMPLES = 10;
		static double frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static double prevTicks = SDL_GetTicks();
		float currentTicks;

		currentTicks = SDL_GetTicks();

		m_frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

		prevTicks = currentTicks;

		int count;
		currentFrame++;

		if (currentFrame < NUM_SAMPLES)
		{
			count = currentFrame;
		}
		else
		{
			count = NUM_SAMPLES;
		}

		double frameTimeAverage = 0;
		for (int i = 0; i < count; i++)
		{
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		if (frameTimeAverage > 0)
		{
			m_FPS = 1000.0f / frameTimeAverage;
		}
		else
		{
			m_FPS = 60.0f;
		}

	}

}