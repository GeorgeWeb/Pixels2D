#pragma once

#ifndef SPRITEFONT_HGUARD
#define SPRITEFONT_HGUARD

#include <SDL/SDL_ttf.h>

#include <glm/glm.hpp>

#include <map>
#include <vector>

#include "Vertex.h"

namespace Pixels2D
{
    class GLTexture;
    class SpriteBatch;

    struct CharGlyph {
    public:
        char character;
        glm::vec4 uvRect;
        glm::vec2 size;
    };

#define FIRST_PRINTABLE_CHAR ((char)32)
#define LAST_PRINTABLE_CHAR ((char)126)

    // for text justification
    enum class Justification
	{
        LEFT,
		MIDDLE,
		RIGHT
    };

    class SpriteFont
	{
    public:
        SpriteFont(const char* font, int size, char cs, char ce);
        SpriteFont(const char* font, int size) : SpriteFont(font, size, FIRST_PRINTABLE_CHAR, LAST_PRINTABLE_CHAR) {}
        
		// destroys the font resources
        void dispose();

        int getFontHeight() const { return m_fontHeight; }

        // measures the dimensions of the text
        glm::vec2 measure(const char* s);

        // draws using a spritebatch
        void draw(SpriteBatch& batch, const char* s, glm::vec2 position, glm::vec2 scaling, float depth, ColorRGBA8 tint, Justification just = Justification::LEFT);
    
	private:
        static std::vector<int>* createRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w);

	private:
        int m_regStart, m_regLength;
        CharGlyph* m_glyphs;
        int m_fontHeight;

        unsigned int m_texID;
    };

}

#endif // !SPRITEFONT_HGUARD