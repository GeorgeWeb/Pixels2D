#include "Timing.h"

#include <SDL/SDL.h>

using namespace Pixels2D;

FPSLimiter::FPSLimiter() // : _maxFPS(60.0f)
{
}

void FPSLimiter::init(const float &maxFPS)
{
	setMaxFPS(maxFPS);
}

void FPSLimiter::setMaxFPS(const float &maxFPS)
{
	_maxFPS = maxFPS;
}

void FPSLimiter::beginFrame()
{
	_startTicks = SDL_GetTicks();
}

const float &FPSLimiter::endFrame()
{	
	calculateFPS();

	// limit the FPS to _maxFPS
	float frameTicks = SDL_GetTicks() - _startTicks;
	if (1000.0f / _maxFPS > frameTicks)
		SDL_Delay(1000.0f / _maxFPS - frameTicks);

	return _fps;
}

void FPSLimiter::calculateFPS()
{
	static const unsigned int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static unsigned int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();

	float currTicks;

	currTicks = SDL_GetTicks();

	_frameTime = currTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currTicks;

	unsigned int count;

	currentFrame++;

	if (currentFrame < NUM_SAMPLES)
		count = currentFrame;
	else
		count = NUM_SAMPLES;

	float frameTimeAverage = 0;

	for (unsigned int i = 0; i < count; i++)
		frameTimeAverage += frameTimes[i];

	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
		_fps = 1000.0f / frameTimeAverage;
	else
		_fps = 60.0f;
}