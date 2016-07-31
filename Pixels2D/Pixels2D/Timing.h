#ifndef TIMING_HGUARD
#define TIMING_HGUARD

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
		float _fps;
		float _maxFPS;
		float _frameTime;

		GLuint _startTicks;
	};
}

#endif // !TIMING_HGUARD