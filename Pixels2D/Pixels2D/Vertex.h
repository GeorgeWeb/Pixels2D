#ifndef VERTEX_HGUARD
#define VERTEX_HGUARD

#include <GL/glew.h>

namespace Pixels2D
{
	// xy
	struct Position
	{
		float x;
		float y;

		// helper position setting function
		void setPosition(const float &x, const float &y)
		{
			this->x = x;
			this->y = y;
		}
	};

	// rgba
	struct Color
	{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;

		// helper color setting function
		void setColor(const GLubyte &r, const GLubyte &g, const GLubyte &b, const GLubyte &a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
	};

	// uv
	struct UV
	{
		float u;
		float v;
	};

	// aligned to 12b
	struct Vertex
	{
		/* members */

		// position coordiante - 2D
		Position position;
		// 4 bytes for r g b a color
		Color color;
		// UV texture coordinate
		UV uv;

		/* member functions */

		// helper position setting function
		void setPosition(const float &x, const float &y)
		{
			position.x = x;
			position.y = y;
		}

		// helper color setting function
		void setColor(const GLubyte &r, const GLubyte &g, const GLubyte &b, const GLubyte &a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		// helper UV setting function
		void setUV(const float &u, const float &v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
}

#endif // !VERTEX_HGUARD