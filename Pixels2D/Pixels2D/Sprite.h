#ifndef SPRITE_HGUARD
#define SPRITE_HGUARD
#ifdef PRAGMA_ONCE
	#pragma once
#endif

#include "GLTexture.h"

#include <GL/glew.h>
#include <string>

namespace Pixels2D
{
	class Sprite
	{
	private:
		float m_x;
		float m_y;
		float m_width;
		float m_height;
		GLuint m_vboID;
		GLTexture m_texture;

	public:
		Sprite();
		~Sprite();

		void init(const float &x, const float &y, const float &width, const float &height, const std::string &texturePath);
		void draw();
		void move();
	};
}

#endif // !SPRITE_HGUARD