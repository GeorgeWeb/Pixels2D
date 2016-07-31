#ifndef RESOURCEMANAGER_HGUARD
#define RESOURCEMANAGER_HGUARD

#include "TextureCache.h"

#include <string>

namespace Pixels2D
{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(const std::string &texturePath);

	private:
		static TextureCache _textureCache;
	};
}

#endif // !RESOURCEMANAGER_HGUARD