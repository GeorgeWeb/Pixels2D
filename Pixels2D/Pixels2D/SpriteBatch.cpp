#include "SpriteBatch.h"

#include <algorithm>

using namespace std;

namespace Pixels2D
{
	Glyph::Glyph()
	{
		// Empty
	}

	Glyph::Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &Texture, const float &Depth, const ColorRGBA8 &color)
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

	Glyph::Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &Texture, const float &Depth, const ColorRGBA8 &color, const float &angle)
		: texture(Texture), depth(Depth)
	{
		const glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

		glm::vec2 tl(-halfDims.x, halfDims.y);
		glm::vec2 bl(-halfDims.x, -halfDims.y);
		glm::vec2 br(halfDims.x, -halfDims.y);
		glm::vec2 tr(halfDims.x, halfDims.y);

		// rotate the points
		tl = rotatePoint(tl, angle) + halfDims;
		bl = rotatePoint(bl, angle) + halfDims;
		br = rotatePoint(br, angle) + halfDims;
		tr = rotatePoint(tr, angle) + halfDims;

		topLeft.setColor(color.r, color.g, color.b, color.a);
		topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		topLeft.setColor(color.r, color.g, color.b, color.a);
		bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		topLeft.setColor(color.r, color.g, color.b, color.a);
		bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topLeft.setColor(color.r, color.g, color.b, color.a);
		topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}

	const glm::vec2 &Glyph::rotatePoint(const glm::vec2 &position, const float &angle)
	{
		return glm::vec2
		(
			position.x * cos(angle) - position.y * sin(angle),	// set x
			position.x * sin(angle) + position.y * cos(angle)	// set y
		);
	}


	SpriteBatch::SpriteBatch() : m_vao(0), m_vbo(0)
	{
		// Empty
	}

	SpriteBatch::~SpriteBatch()
	{
		// Empty
	}

	void SpriteBatch::init()
	{
		createVertexArray();
	}

	void SpriteBatch::begin(const GlyphSortType &sortType)
	{
		m_sortType = sortType;
		m_renderBatches.clear();
		m_glyphs.clear();
	}

	void SpriteBatch::end()
	{
		// set up all glyph for faster sorting
		m_glyphPointers.resize(m_glyphs.size());
		for (int i = 0; i < m_glyphs.size(); i++)
			m_glyphPointers[i] = &m_glyphs[i];

		sortGlyphs();
		createRenderBatches();
	}

	// x and y for position; z and w for dimensions
	void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &texture, const float &depth, const ColorRGBA8 &color)
	{
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
	}

	void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &texture, const float &depth, const ColorRGBA8 &color, const float &angle)
	{
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
	}

	void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &texture, const float &depth, const ColorRGBA8 &color, const glm::vec2 &direction)
	{
		const glm::vec2 right(1.0f, 0.0f);
		float angle = acos(glm::dot(right, direction));
		
		if (direction.y < 0)
			angle = -angle;

		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(m_vao);

		for (auto batch : m_renderBatches)
		{
			glBindTexture(GL_TEXTURE_2D, batch.texture);
			glDrawArrays(GL_TRIANGLES, batch.offset, batch.numVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createVertexArray()
	{
		// generate vertex arrays
		if (m_vao == 0)
			glGenVertexArrays(1, &m_vao);

		// bind vertex array object
		glBindVertexArray(m_vao);

		// generate buffers
		if (m_vbo == 0)
			glGenBuffers(1, &m_vbo);

		// bind buffers
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		// enable the vertex attrib array
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// setting the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		// setting the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		// setting the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		// disable the vertex attrib arrays
		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches()
	{
		vector<Vertex> vertices;

		// not 'reserving' because now I can treat it as an array, setting values with '[]', which is way faster than using 'push_back()'
		vertices.resize(m_glyphs.size() * 6);

		if (m_glyphs.empty()) return;

		unsigned int offset = 0;
		unsigned int cv = 0; // current vertex
		m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);
		vertices[cv++] = m_glyphPointers[0]->topLeft;
		vertices[cv++] = m_glyphPointers[0]->bottomLeft;
		vertices[cv++] = m_glyphPointers[0]->bottomRight;
		vertices[cv++] = m_glyphPointers[0]->bottomRight;
		vertices[cv++] = m_glyphPointers[0]->topRight;
		vertices[cv++] = m_glyphPointers[0]->topLeft;
		offset += 6;

		unsigned int cg = 1; // current glyph
		for (; cg < m_glyphs.size(); cg++)
		{
			if (m_glyphPointers[cg]->texture != m_glyphPointers[cg - 1]->texture)
				m_renderBatches.emplace_back(offset, 6, m_glyphPointers[cg]->texture);
			else
				m_renderBatches.back().numVertices += 6;

			vertices[cv++] = m_glyphPointers[cg]->topLeft;
			vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
			vertices[cv++] = m_glyphPointers[cg]->bottomRight;
			vertices[cv++] = m_glyphPointers[cg]->bottomRight;
			vertices[cv++] = m_glyphPointers[cg]->topRight;
			vertices[cv++] = m_glyphPointers[cg]->topLeft;
			offset += 6;
		}

		// bind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		// upload the data to buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data()); // &(vertices[0])
		// unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::sortGlyphs()
	{
		// the stable sort algorithm (though it's slower than the default/quick sort) will make sure that equal textures will remain in the correct order
		switch (m_sortType)
		{
		case GlyphSortType::NONE:
			break;

		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
			break;

		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
			break;

		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
			break;
		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph *a, Glyph *b)
	{
		return a->depth < b->depth;
	}

	bool SpriteBatch::compareBackToFront(Glyph *a, Glyph *b)
	{
		return a->depth > b->depth;
	}

	bool SpriteBatch::compareTexture(Glyph *a, Glyph *b)
	{
		return a->texture < b->texture;
	}
}