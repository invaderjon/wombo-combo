#include "DumbParticleEffect.h"

using namespace graphics;

DumbParticleEffect::DumbParticleEffect(GEint maxParticles)
	: mParticles(), mMaxParticles(maxParticles)
{
	srand(time(NULL));
}


DumbParticleEffect::~DumbParticleEffect()
{
}

void DumbParticleEffect::push(Program* program)
{
	// create vertex array
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// create and bind buffers
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mMaxParticles * sizeof(Particle), NULL, GL_DYNAMIC_DRAW);

	// set attributes
	glVertexAttribPointer(program->resource("vInitPos"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
	glVertexAttribPointer(program->resource("vInitVel"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(3 * sizeof(GEfloat)));
	glVertexAttribPointer(program->resource("vAcc"), 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(6 * sizeof(GEfloat)));
	glVertexAttribPointer(program->resource("dAge"), 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(9 * sizeof(GEfloat)));

	// enable attributes
	glEnableVertexAttribArray(program->resource("vInitPos"));
	glEnableVertexAttribArray(program->resource("vInitVel"));
	glEnableVertexAttribArray(program->resource("vAcc"));
	glEnableVertexAttribArray(program->resource("dAge"));

	// unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unbind VAO
	glBindVertexArray(0);
}

void DumbParticleEffect::update(Mat4* viewMatrix, GEdouble dt)
{
	mModelMatrix = Mat4();
	mModelMatrix[0][0] = mModelMatrix[1][1] = mModelMatrix[2][2] = mModelMatrix[3][3] = 1.0f;
	Mat3 modelView = Mat3(mModelMatrix * *viewMatrix);
	mNormalMatrix = glm::inverseTranspose(modelView);

	// updates items ages while removing dead particles
	for (auto iter = mParticles.begin(); iter != mParticles.end();)
	{
		// update age
		iter->age += dt;

		// check if alive
		if (iter->age > iter->TTL)
			iter = mParticles.erase(iter);
		else
			++iter;
	}

	// try to create new particles
	spawn();

	// push new particle data
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	if (mParticles.size() > 0)
		glBufferSubData(GL_ARRAY_BUFFER, 0, mParticles.size() * sizeof(Particle), &mParticles[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DumbParticleEffect::render(Program* program)
{
	// updates matrices
	glUniformMatrix4fv(program->resource(MAT_MODEL), 1, GL_FALSE, glm::value_ptr(mModelMatrix));

	// draw particles
	glBindVertexArray(mVAO);
	glDrawArrays(GL_POINTS, 0, mParticles.size());
	glBindVertexArray(0);
}

void DumbParticleEffect::spawn()
{
	// stop if there are already too many particles
	if (mParticles.size() > mMaxParticles)
		return;
	// probability that a new particle is generated
	while (rand() % 100 < 96)
	{
		Particle p;
		Quat xq = glm::angleAxis(random(-M_PI / 20, M_PI / 20), Vec3(1, 0, 0));
		Quat zq = glm::angleAxis(random(0, M_PI), Vec3(0, 0, 1));
		p.initPos = Vec3(
			random(-.015f, 0.015f),
			random(-.015f, 0.015f),
			0);
		p.initVel = Vec3(0, 0, random(3.5f, 4.0f));
		p.initVel = Vec3(p.initVel * xq * zq);
		p.acc = Vec3(0, 0, -2.23f);
		p.age = 0;

		// its time to live is calculated by the time it will take to complete it's arc plus one frame for safety
		p.TTL = (-2.0f * (p.initVel.z / p.acc.z));

		// pushes particle to list
		mParticles.push_back(p);
	}
}

GEfloat DumbParticleEffect::random(GEfloat minimum, GEfloat maximum)
{
	GEfloat mult = static_cast <GEfloat> (rand()) / static_cast <GEfloat> (RAND_MAX);
	GEfloat diff = maximum - minimum;
	return mult*diff + minimum;
}