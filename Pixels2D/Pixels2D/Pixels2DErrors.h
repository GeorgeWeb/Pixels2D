#ifndef PIXELS2DERRORS_HGUARD
#define PIXELS2DERRORS_HGUARD

// inlcude SDL
#include <SDL/SDL.h>
// include GLEW
#include <GL/glew.h>

#include <string>

namespace Pixels2D
{

	class Errors
	{
	public:
		static void fatalError(std::string errorString);
	};
}

#endif // !PIXELS2DERRORS_HGUARD