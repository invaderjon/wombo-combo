#include "ParticleController.h"

using namespace graphics;

ParticleController::ParticleController(ParticleData& data)
	: mData(data), mRand()
{
	// init rand
	srand(time(0));

	// sin func offsets
	mOffsets = new GEfloat[data.count()];

	// starts off with 1/10th of the particles alive
	add(mData.count() / 10);
}

ParticleController::~ParticleController()
{
}

void ParticleController::update(GEdouble elapsed)
{
	// iterate through all of the alive particles
	for (GEint i = 0; i < mData.alive(); ++i)
	{
		// perform an update on the particle
		function(mData[i], elapsed);

		// is the particle dead?
		if (mData[i].ttl < mData[i].age)
		{
			// if it's not already at the end
			if (i < mData.alive())
			{
				// swap with last known alive item
				mData.swap(i, mData.alive() - 1);

				// recheck current index since it'll be a new item
				--i;
			}

			// decriment the number of alive items
			mData.alive(mData.alive() - 1);
		}

		// spawn new items
		spawn();
	}
}


void ParticleController::function(ParticleData::Particle& p, GEdouble elapsed)
{
	// update particle's age
	p.age += GEfloat(elapsed);
	
	// updates acceleration
	p.acc = Vec3(0, mRand.next(-1.0f, 1.0f) + sinf(p.age), 0);

	// applies acceleration
	p.vel += p.acc * GEfloat(elapsed);

	// applies velocity
	p.pos += p.vel * GEfloat(elapsed);
	
}

void ParticleController::spawn()
{
	// calculate number of items to spawn
	GEint minimum = mData.count() / 100;
	GEint maximum = 2*(mData.count() / 100);

	// ensure max is at least two
	maximum = (maximum >= 2) ? maximum : 2;

	// calculate count
	GEint count = mRand.next(minimum, maximum);

	// add that many items
	add(count);
}

void ParticleController::add(GEint count)
{
	// prevent from going over max size
	if (mData.alive() + count > mData.count())
		count = mData.count() - mData.alive();

	// add so long as there are more to add
	while (count-- > 0)
	{
		// give it an offset
		mOffsets[mData.alive()] = mRand.next(0.0f, GEfloat(M_PI));

		// initialize new particle
		ParticleData::Particle p = mData[mData.alive()];
		p.pos = Vec3(mRand.next(-.25f, .25f), mRand.next(-.05f, .05f), 0);
		p.vel = Vec3(0, 0, mRand.next(.75f, 1.5f));
		p.acc = Vec3(0.0f, 0.0f, 0.0f);
		p.col = Vec4(1.0, 1.0, 1.0, 1.0);
		p.ttl = mOffsets[mData.alive()] + mRand.next(3.0f, 4.0f);
		p.age = mOffsets[mData.alive()];
		p.size = mRand.next(.25f, .5f);
		mData[mData.alive()] = p;

		// update alive count
		mData.alive(mData.alive() + 1);
	}
}