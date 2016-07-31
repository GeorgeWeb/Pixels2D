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

	struct Glyph
	{
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
				: offset(aOffset), numVertices(aNumVertices), texture(aTexture)
			{}

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
		void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &texture, const float &depth, const Color &color);

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

		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatch> _renderBatches;
	};
}

#endif // !SPRITEBATCH_HGUARD