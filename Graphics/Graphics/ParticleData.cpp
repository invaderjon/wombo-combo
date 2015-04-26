#include "ParticleData.h"

using namespace graphics;

ParticleData::ParticleData(GEint count)
	: mSrcFunc(GL_ONE), mDstFunc(GL_ZERO), mAlive(0), mCount(count)
{
	mParticles = new Particle[count];
}

ParticleData::ParticleData(GEint count, GEenum srcFunc, GEenum dstFunc)
	: mSrcFunc(srcFunc), mDstFunc(dstFunc), mAlive(0), mCount(count)
{
	mParticles	= new Particle[count];
}

ParticleData::~ParticleData()
{
	delete mParticles;
}

ParticleData::Particle& ParticleData::operator[] (GEint i)
{
	return mParticles[i];
}

const ParticleData::Particle& ParticleData::operator[] (GEint i) const
{
	return mParticles[i];
}

void ParticleData::swap(GEint a, GEint b)
{
	// performs swap
	Particle p(mParticles[a]);
	mParticles[a] = mParticles[b];
	mParticles[b] = p;
}

GEint ParticleData::alive() const
{
	return mAlive;
}

void ParticleData::alive(GEint count)
{
	mAlive = count;
}

GEint ParticleData::count() const
{
	return mCount;
}

GEenum ParticleData::srcFunc() const
{
	return mSrcFunc;
}

GEenum ParticleData::dstFunc() const
{
	return mDstFunc;
}