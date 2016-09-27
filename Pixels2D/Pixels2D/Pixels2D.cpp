#include "Pixels2D.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

namespace Pixels2D
{
	int init()
	{
		// initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		// set double buffered window to avoid flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}