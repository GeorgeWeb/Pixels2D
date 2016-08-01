#include "ParticleEngine2D.h"

namespace Pixels2D
{
	ParticleEngine2D::ParticleEngine2D()
	{
	}

	ParticleEngine2D::~ParticleEngine2D()
	{
		for (auto &batch : m_batches)
			delete batch;
	}

	void ParticleEngine2D::addParticleBatch(ParticleBatch2D *paticleBatch)
	{
		m_batches.push_back(paticleBatch);
	}

	void ParticleEngine2D::update(const float &deltaTime)
	{
		for (auto &batch : m_batches)
			batch->update(deltaTime);
	}

	void ParticleEngine2D::draw(SpriteBatch *spriteBatch)
	{
		for(auto &batch : m_batches)
		{
			spriteBatch->begin();

			batch->draw(spriteBatch);

			spriteBatch->end();
			spriteBatch->renderBatch();
		}
	}
}