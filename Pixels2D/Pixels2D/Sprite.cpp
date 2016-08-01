#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

using namespace Pixels2D;

Sprite::Sprite() : m_vboID(0)
{}

Sprite::~Sprite()
{
	// clean up
	if (m_vboID != 0)
		glDeleteBuffers(1, &m_vboID);
}

void Sprite::init(const float &x, const float &y, const float &width, const float &height, const std::string &texturePath)
{
	m_x = x;
	m_y = x;
	m_width = width;
	m_height = height;
	m_texture = ResourceManager::getTexture(texturePath);

	// generate buffers
	if (m_vboID == 0)
		glGenBuffers(1, &m_vboID);

	// 6 vertices
	Vertex vertexData[6];
	
	/* set position */
	
	// first triangle
	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].setPosition(x, y + height);
	vertexData[1].setUV(0.0f, 1.0f);
	
	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0.0f, 0.0f);

	// second Triangle
	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].setPosition(x + width , y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1.0f, 1.0f);
	
	/* set color */

	for (unsigned int i = 0; i < 6; i++)
		vertexData[i].setColor(255, 0, 255, 255);
	
	vertexData[1].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);

	// bind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	// upload data to the gpu
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	// unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	// bind the texture
	glBindTexture(GL_TEXTURE_2D, m_texture.id);

	// bind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	// draw the 6 vertices to the screen
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}