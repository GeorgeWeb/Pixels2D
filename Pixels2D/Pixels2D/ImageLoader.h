#ifndef IMAGELOADER_HGUARD
#define IMAGELOADER_HGUARD

#include "GLTexture.h"

#include <string>


namespace Pixels2D
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(const std::string &filePath);
	};
}

#endif // !IMAGELOADER_HGUARD