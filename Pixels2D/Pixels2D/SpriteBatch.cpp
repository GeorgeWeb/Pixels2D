#include "SpriteBatch.h"

#include <algorithm>

using namespace std;
using namespace Pixels2D;

SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
{
}

SpriteBatch::~SpriteBatch()
{
	/*
	// empty memory to avoid possible leaks
	if (!_glyphs.empty())
	{
		for (vector<Glyph*>::iterator it = _glyphs.begin(); it != _glyphs.end(); it++)
		{
			delete[] * it;
			*it = nullptr;
		}
	}
	*/
}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(const GlyphSortType &sortType)
{
	_sortType = sortType;
	_renderBatches.clear();
	if (!_glyphs.empty())
	{
		for (vector<Glyph*>::iterator glyph_iter = _glyphs.begin(); glyph_iter != _glyphs.end(); glyph_iter++)
		{
			delete[] *glyph_iter;
			*glyph_iter = nullptr;
		}
	}
	_glyphs.clear();
}

void SpriteBatch::end()
{
	sortGlyphs();
	createRenderBatches();
}

// x and y for position; z and w for dimensions
void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, const GLuint &texture, const float &depth, const Color &color)
{
	Glyph *newGlyph = new Glyph;
	newGlyph->texture = texture;
	newGlyph->depth = depth;

	newGlyph->topLeft.setColor(color.r, color.g, color.b, color.a);
	newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	newGlyph->topLeft.setColor(color.r, color.g, color.b, color.a);
	newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
	newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

	newGlyph->topLeft.setColor(color.r, color.g, color.b, color.a);
	newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	newGlyph->topLeft.setColor(color.r, color.g, color.b, color.a);
	newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	_glyphs.push_back(newGlyph);
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
	if(_vao == 0)
		glGenVertexArrays(1, &_vao);
	
	// bind vertex array object
	glBindVertexArray(_vao);

	// generate buffers
	if(_vbo == 0)
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
	_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
	vertices[cv++] = _glyphs[0]->topLeft;
	vertices[cv++] = _glyphs[0]->bottomLeft;
	vertices[cv++] = _glyphs[0]->bottomRight;
	vertices[cv++] = _glyphs[0]->bottomRight;
	vertices[cv++] = _glyphs[0]->topRight;
	vertices[cv++] = _glyphs[0]->topLeft;
	offset += 6;

	unsigned int cg = 1; // current glyph
	for (; cg < _glyphs.size(); cg++)
	{
		if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture)
			_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
		else
			_renderBatches.back().numVertices += 6;

		vertices[cv++] = _glyphs[cg]->topLeft;
		vertices[cv++] = _glyphs[cg]->bottomLeft;
		vertices[cv++] = _glyphs[cg]->bottomRight;
		vertices[cv++] = _glyphs[cg]->bottomRight;
		vertices[cv++] = _glyphs[cg]->topRight;
		vertices[cv++] = _glyphs[cg]->topLeft;
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
	// the stable sort algorithm (though it's the slower one) will make sure that equal textures will remain in the correct order
	switch (_sortType)
	{
		case GlyphSortType::NONE:
			break;
		
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
			break;
		
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
			break;

		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
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