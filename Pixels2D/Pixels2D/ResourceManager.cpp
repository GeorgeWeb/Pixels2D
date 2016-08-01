#include "ResourceManager.h"

using namespace std;

namespace Pixels2D
{
	TextureCache ResourceManager::m_textureCache;

	GLTexture ResourceManager::getTexture(const std::string &texturePath)
	{
		return m_textureCache.getTexture(texturePath);
	}
}