#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Random.h"
#include "ParticleData.h"

namespace graphics
{
	class ParticleController
	{
	public:
		ParticleController(ParticleData& data);
		~ParticleController();

		// updates particles using a given ellapsed time
		void update(GEdouble elapsed);

	private:
		// particle update function
		inline void function(ParticleData::Particle& particle, GEdouble elapsed);
		// particle spawn function
		inline void spawn();
		// generates and adds specified number of items
		inline void add(GEint count);
		
		ParticleData& mData;
		GEfloat* mOffsets;
		Random mRand;
	};
}

