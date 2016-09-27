#ifndef SPRITEBATCH_HGUARD
#define SPRITEBATCH_HGUARD
#ifdef PRAGMA_ONCE
	#pragma once
#endif

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
		Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &Texture, const float &Depth, const ColorRGBA8 &color);
		Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &Texture, const float &Depth, const ColorRGBA8 &color, const float &angle);

	public:
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	
	private:
		inline const glm::vec2 &rotatePoint(const glm::vec2 &position, const float &angle);
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
		void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &texture, const float &depth, const ColorRGBA8 &color, const float &angle);
		void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &texture, const float &depth, const ColorRGBA8 &color, const glm::vec2 &direction);

		void renderBatch();
	
	private:
		void createVertexArray();
		void createRenderBatches();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph *a, Glyph *b);
		static bool compareBackToFront(Glyph *a, Glyph *b);
		static bool compareTexture(Glyph *a, Glyph *b);

	private:
		GLuint m_vbo;
		GLuint m_vao;

		GlyphSortType m_sortType;

		// using this just for sorting
		std::vector<Glyph*> m_glyphPointers;
		// these are going to be the actual glyphs
		std::vector<Glyph> m_glyphs;

		std::vector<RenderBatch> m_renderBatches;
	};
}

#endif // !SPRITEBATCH_HGUARD