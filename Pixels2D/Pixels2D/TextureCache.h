#ifndef TEXTURECACHE_HGUARD
#define TEXTURECACHE_HGUARD

#include "GLTexture.h"

#include <map>
#include <string>

namespace Pixels2D
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(const std::string &texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;

	};
}

#endif // !TEXTURECACHE_HGUARD