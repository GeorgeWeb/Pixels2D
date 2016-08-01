#pragma once

#ifndef PARTICLEBATCH2D_HGUARD
#define PARTICLEBATCH2D_HGUARD

#include "Vertex.h"
#include "SpriteBatch.h"

#include <glm/glm.hpp>

#include <functional>

namespace Pixels2D
{		
	struct Particle2D
	{
		glm::vec2 position = glm::vec2(0.0f);
		glm::vec2 velocity = glm::vec2(0.0f);
		Pixels2D::ColorRGBA8 color;
		float life = 0.0f;
		float width = 0.0f;
	};

	inline void defaultParticleupdate(Particle2D &particle, const float &deltaTime)
	{
		particle.position += particle.velocity * deltaTime;
	}

	class ParticleBatch2D
	{
	public:
		ParticleBatch2D();
		~ParticleBatch2D();

		// initializes the particle batch
		void init(const int &maxParticles, const float &decayRate, const GLuint &textureID,
			std::function<void(Particle2D&, float)> updateFunc = defaultParticleupdate);

		// updates the particle batch
		void update(const float &deltaTime);

		// draws the particles
		void draw(SpriteBatch *spriteBatch);

		// adds a particle
		void addParticle(const glm::vec2 &position, const glm::vec2 &velocity, const ColorRGBA8 &color, const float &width);

	private:
		int findFreeParticle();

	private:
		std::function<void(Particle2D&, float)> m_updateFunc;

		float m_decayRate = 0.1f;
		Particle2D *m_particles = nullptr;
		int m_maxParticles = 0;
		int m_lastFreeParticle = 0;
		GLuint m_textureID;
	};
}

#endif // !PARTICLEBATCH2D_HGUARD

