#ifndef SPRITE_HGUARD
#define SPRITE_HGUARD

#include "GLTexture.h"

#include <GL/glew.h>
#include <string>

namespace Pixels2D
{
	class Sprite
	{
	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID;
		GLTexture _texture;

	public:
		Sprite();
		~Sprite();

		void init(const float &x, const float &y, const float &width, const float &height, const std::string &texturePath);
		void draw();
		void move();
	};
}

#endif // !SPRITE_HGUARD