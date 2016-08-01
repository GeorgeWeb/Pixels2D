#pragma once

#ifndef SPRITEBATCH_HGUARD
#define SPRITEBATCH_HGUARD

#include "Vertex.h"

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <vector>

namespace Pixels2D
{
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	class Glyph
	{
	public:
		Glyph();
		Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &Texture, const float &Depth, const ColorRGBA8 &color)
			: texture(Texture), depth(Depth)
		{
			topLeft.setColor(color.r, color.g, color.b, color.a);
			topLeft.setPosition(destRect.x, destRect.y + destRect.w);
			topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

			topLeft.setColor(color.r, color.g, color.b, color.a);
			bottomLeft.setPosition(destRect.x, destRect.y);
			bottomLeft.setUV(uvRect.x, uvRect.y);

			topLeft.setColor(color.r, color.g, color.b, color.a);
			bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
			bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

			topLeft.setColor(color.r, color.g, color.b, color.a);
			topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
			topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		}

	public:
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class RenderBatch
	{
	public:
		RenderBatch(const GLuint &aOffset, const GLuint &aNumVertices, const GLuint &aTexture)
			: offset(aOffset), numVertices(aNumVertices), texture(aTexture)	{}

		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();
		
		void begin(const GlyphSortType &sortType = GlyphSortType::TEXTURE);
		void end();

		// x and y for position; z and w for dimensions
		void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &texture, const float &depth, const ColorRGBA8 &color);

		void renderBatch();
	
	private:
		void createVertexArray();
		void createRenderBatches();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph *a, Glyph *b);
		static bool compareBackToFront(Glyph *a, Glyph *b);
		static bool compareTexture(Glyph *a, Glyph *b);

	private:
		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;

		// using this just for sorting
		std::vector<Glyph*> m_glyphPointers;
		// these are going to be the actual glyphs
		std::vector<Glyph> m_glyphs;

		std::vector<RenderBatch> m_renderBatches;
	};
}

#endif // !SPRITEBATCH_HGUARD