#ifndef PARTICLEENGINE2D_HGUARD
#define PARTICLEENGINE2D_HGUARD
#ifdef PRAGMA_ONCE
	#pragma once
#endif

#include "ParticleBatch2D.h"
#include "SpriteBatch.h"

#include <vector>

namespace Pixels2D
{
	class ParticleEngine2D
	{
	public:
		ParticleEngine2D();
		~ParticleEngine2D();

		// after adding a particle batch, the particle engine becomes responsible for deallocation
		void addParticleBatch(ParticleBatch2D *paticleBatch);

		void update(const float &deltaTime);

		void draw(SpriteBatch *spriteBatch);

	private:
		std::vector<ParticleBatch2D*> m_batches;
	};
}

#endif !PARTICLEENGINE2D_HGUARD