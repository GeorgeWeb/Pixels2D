#ifndef VERTEX_HGUARD
#define VERTEX_HGUARD

#include <GL/glew.h>

namespace Pixels2D
{
	// xy
	struct Position
	{
		Position() : x(0.0f), y(0.0f) {}
		Position(const float &X, const float &Y) : x(X), y(Y) {}

		float x;
		float y;
	};

	// rgba
	struct ColorRGBA8
	{
		ColorRGBA8() : r(0), g(0), b(0), a(0) {}
		ColorRGBA8(const GLubyte &R, const GLubyte &G, const GLubyte &B, const GLubyte &A) 
			: r(R), g(G), b(B), a(A) {}

		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	// uv
	struct UV
	{
		UV() : u(0.0f), v(0.0f) {}
		UV(const float &U, const float &V) : u(U), v(V) {}

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
		ColorRGBA8 color;
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