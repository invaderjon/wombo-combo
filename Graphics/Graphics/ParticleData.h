#pragma once

#include <vector>
#include "Graphics.h"

using namespace std;

namespace graphics
{

	class ParticleData
	{
	public:
		// Note to professor,
		// I was going to make all of the different particle variables
		// different arrays entirely so only the necessary fields were
		// passed to the gpu but then I realized how ridiculous simple
		// update operations would be. I may change it if it proves to
		// be a bottleneck but for now I don't think it should be too
		// big an issue since I'm not doing anything crazy like a
		// million+ particle system.
		typedef struct	sParticle
		{
			Vec3		pos;
			Vec3		vel;
			Vec3		acc;
			Vec4		col;
			GEfloat		age;
			GEfloat		ttl;
			GEfloat		size;
		}				Particle;

		ParticleData(GEint count);
		ParticleData(GEint count, GEenum srcFunc, GEenum dstFunc);
		~ParticleData();

		// particle accessor methods
		Particle& operator[](GEint i);
		const Particle& operator[](GEint i) const;

		// swaps two items
		void swap(GEint a, GEint b);

		// get or set number of items alive
		GEint alive() const;
		void alive(GEint count);

		// gets the count
		GEint count() const;

		// gets the blend functions
		GEenum srcFunc() const;
		GEenum dstFunc() const;

	private:
		Particle* mParticles;
		GEint mAlive;
		GEint mCount;
		GEenum mSrcFunc;
		GEenum mDstFunc;
	};

}
