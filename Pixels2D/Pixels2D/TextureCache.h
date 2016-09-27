#ifndef TEXTURECACHE_HGUARD
#define TEXTURECACHE_HGUARD
#ifdef PRAGMA_ONCE
	#pragma once
#endif

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
		std::map<std::string, GLTexture> m_textureMap;

	};
}

#endif // !TEXTURECACHE_HGUARD