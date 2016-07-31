#include "ResourceManager.h"

using namespace std;

namespace Pixels2D
{
	TextureCache ResourceManager::_textureCache;

	GLTexture ResourceManager::getTexture(const std::string &texturePath)
	{
		return _textureCache.getTexture(texturePath);
	}
}