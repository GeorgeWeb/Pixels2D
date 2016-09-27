#ifndef GLTEXTURE_HGUARD
#define GLTEXTURE_HGUARD
#ifdef PRAGMA_ONCE
	#pragma once
#endif

#include <GL/glew.h>

namespace Pixels2D
{
	struct GLTexture
	{
		GLuint id;
		int width;
		int height;
	};
}

#endif // !GLTEXTURE_HGUARD

