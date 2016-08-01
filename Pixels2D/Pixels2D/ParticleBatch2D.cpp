#include "ParticleBatch2D.h"
#include "ResourceManager.h"

namespace Pixels2D
{
	ParticleBatch2D::ParticleBatch2D()
	{
	}

	ParticleBatch2D::~ParticleBatch2D()
	{
		delete[] m_particles;
	}

	void ParticleBatch2D::init(const int &maxParticles, const float &decayRate, const GLuint &textureID,
		std::function<void(Particle2D&, float)> updateFunc)
	{
		m_maxParticles = maxParticles;
		m_particles = new Particle2D[maxParticles];
		m_decayRate = decayRate;
		m_textureID = textureID;
		m_updateFunc = updateFunc;
	}

	void ParticleBatch2D::update(const float &deltaTime)
	{
		for (int i = 0; i < m_maxParticles; i++)
		{
			// check if it is active
			if (m_particles[i].life > 0.0f)
			{
				m_updateFunc(m_particles[i], deltaTime);
				m_particles[i].life -= m_decayRate * deltaTime;
			}
		}
	}
	
	void ParticleBatch2D::draw(SpriteBatch *spriteBatch)
	{
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		for (int i = 0; i < m_maxParticles; i++)
		{
			// check if it is active
			auto &part = m_particles[i];
			if (part.life > 0.0f)
			{
				glm::vec4 destRect(part.position.x, part.position.y, part.width, part.width);

				spriteBatch->draw(destRect, uvRect, m_textureID, 0.0f, part.color);
			}
		}
	}

	void ParticleBatch2D::addParticle(const glm::vec2 &position, const glm::vec2 &velocity, const ColorRGBA8 &color, const float &width)
	{
		int particleIndex = findFreeParticle();

		auto& part = m_particles[particleIndex];

		part.life = 1.0f;
		part.position = position;
		part.velocity = velocity;
		part.color = color;
		part.width = width;
	}

	int ParticleBatch2D::findFreeParticle()
	{
		for (int i = m_lastFreeParticle; i < m_maxParticles; i++)
		{
			if (m_particles[i].life <= 0.0f)
			{
				m_lastFreeParticle = i;
				return i;
			}
		}

		for (int i = 0; i < m_lastFreeParticle; i++)
		{
			if (m_particles[i].life <= 0.0f)
			{
				m_lastFreeParticle = i;
				return i;
			}
		}

		// no particles are free, ovveride the first one
		return 0;
	}
}
