#include "SpriteBatch.h"

#include <algorithm>

using namespace std;
using namespace Pixels2D;

SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(const GlyphSortType &sortType)
{
	_sortType = sortType;
	_renderBatches.clear();
	_glyphs.clear();
}

void SpriteBatch::end()
{
	// set up all glyph for faster sorting
	_glyphPointers.resize(_glyphs.size());
	for (int i = 0; i < _glyphs.size(); i++)
		_glyphPointers[i] = &_glyphs[i];

	sortGlyphs();
	createRenderBatches();
}

// x and y for position; z and w for dimensions
void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &texture, const float &depth, const ColorRGBA8 &color)
{
	_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(_vao);

	for (auto batch : _renderBatches)
	{
		glBindTexture(GL_TEXTURE_2D, batch.texture);
		glDrawArrays(GL_TRIANGLES, batch.offset, batch.numVertices);
	}

	glBindVertexArray(0);
}

void SpriteBatch::createVertexArray()
{
	// generate vertex arrays
	if (_vao == 0)
		glGenVertexArrays(1, &_vao);

	// bind vertex array object
	glBindVertexArray(_vao);

	// generate buffers
	if (_vbo == 0)
		glGenBuffers(1, &_vbo);

	// bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

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
	vertices.resize(_glyphs.size() * 6);

	if (_glyphs.empty()) return;

	unsigned int offset = 0;
	unsigned int cv = 0; // current vertex
	_renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);
	vertices[cv++] = _glyphPointers[0]->topLeft;
	vertices[cv++] = _glyphPointers[0]->bottomLeft;
	vertices[cv++] = _glyphPointers[0]->bottomRight;
	vertices[cv++] = _glyphPointers[0]->bottomRight;
	vertices[cv++] = _glyphPointers[0]->topRight;
	vertices[cv++] = _glyphPointers[0]->topLeft;
	offset += 6;

	unsigned int cg = 1; // current glyph
	for (; cg < _glyphs.size(); cg++)
	{
		if (_glyphPointers[cg]->texture != _glyphPointers[cg - 1]->texture)
			_renderBatches.emplace_back(offset, 6, _glyphPointers[cg]->texture);
		else
			_renderBatches.back().numVertices += 6;

		vertices[cv++] = _glyphPointers[cg]->topLeft;
		vertices[cv++] = _glyphPointers[cg]->bottomLeft;
		vertices[cv++] = _glyphPointers[cg]->bottomRight;
		vertices[cv++] = _glyphPointers[cg]->bottomRight;
		vertices[cv++] = _glyphPointers[cg]->topRight;
		vertices[cv++] = _glyphPointers[cg]->topLeft;
		offset += 6;
	}

	// bind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
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
	switch (_sortType)
	{
	case GlyphSortType::NONE:
		break;

	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFrontToBack);
		break;

	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareBackToFront);
		break;

	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
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