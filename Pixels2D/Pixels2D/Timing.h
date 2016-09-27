#ifndef TIMING_HGUARD
#define TIMING_HGUARD
#ifdef PRAGMA_ONCE
	#pragma once
#endif

#include <GL/glew.h>

namespace Pixels2D
{
	class FPSLimiter
	{
	public:
		FPSLimiter();
		void init(const float &maxFPS);
		
		void setMaxFPS(const float &maxFPS);
			
		void beginFrame();
		const float &endFrame(); // will return the current FPS

	private:
		void calculateFPS();

	private:
		float m_fps;
		float m_maxFPS;
		float m_frameTime;

		GLuint m_startTicks;
	};
}

#endif // !TIMING_HGUARD