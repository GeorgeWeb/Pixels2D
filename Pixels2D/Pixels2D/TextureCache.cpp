#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>

using namespace std;
using namespace Pixels2D;

TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(const string &texturePath)
{
	// lookup the texture and check if it is the map
	auto mit = m_textureMap.find(texturePath); // returns map iterator

	// check if it is not in the map (and load it)
	if (mit == m_textureMap.end())
	{
		// load the texture
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);
		// insert the texture into the map
		m_textureMap.insert(make_pair(texturePath, newTexture));
		
		// returns a new texture
		return newTexture;
	}
	// returns a cached texture
	return mit->second;
}
