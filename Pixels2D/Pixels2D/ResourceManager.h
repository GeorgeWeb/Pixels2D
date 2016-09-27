#ifndef RESOURCEMANAGER_HGUARD
#define RESOURCEMANAGER_HGUARD
#ifdef PRAGMA_ONCE
	#pragma once
#endif

#include "TextureCache.h"

#include <string>

namespace Pixels2D
{
	class ResourceManager
	{
	public:
		static GLTexture getTexture(const std::string &texturePath);

	private:
		static TextureCache m_textureCache;
	};
}

#endif // !RESOURCEMANAGER_HGUARD