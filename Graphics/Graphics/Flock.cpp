#include "Flock.h"

using namespace graphics;

Flock::Flock(GEuint count, GEfloat radius)
	: mCount(count)
{
	mBoids = new Boid[count];
	mTemp = new Boid[count]; // used to store updates

	// creates rules
	mRuleCount = 4;
	mRules = new IRule*[mRuleCount];
	mRules[0] = new SeperationRule();
	mRules[1] = new AlignmentRule();
	mRules[2] = new CohesionRule();
	mRules[3] = new RadiusRule();
	
	// inits boids
	for (GEuint i = 0; i < count; i++)
	{
		mBoids[i] = Boid(radius);
	}

	// creates transformation matrices
	mMatrices = new Mat4[count * 2];
}


Flock::~Flock()
{
	// deletes dynamic data
	delete mBoids;
	delete mTemp;
	delete mMatrices;
	for (GEuint i = 0; i < mRuleCount; ++i)
	{
		delete mRules[i];
	}
	delete mRules;
}

void Flock::applyRules(GEdouble elapsed)
{
	GEuint i;
	GEuint j;
	Boid b;
	// applies each rule to each boid
	for (i = 0; i < mCount; i++)
	{
		b = mBoids[i];
		Vec3 v = b.vel;
		mTemp[i] = mBoids[i];
		for (j = 0; j < mRuleCount; j++)
		{
			v += mRules[j]->apply(i, mBoids, mCount);
		}

		// limit to max speed
		if (glm::length(v) > BOID_MAX_VELOCITY)
			v = glm::normalize(v) * BOID_MAX_VELOCITY;

		// keeps inside of bounds
		//if (glm::length(v + b.pos) > 2.0f)
		//	v -= v * 2.0f;

		mTemp[i] = Boid(b.pos + (v * (GEfloat)elapsed), v);
	}

	// copies over resulting temp values
	for (i = 0; i < mCount; i++)
		mBoids[i] = mTemp[i];
	//printf("Boid[pos:<%f,%f,%f>\tvel:<%f,%f,%f>]\n", p.x, p.y, p.z, v.x, v.y, v.z);
}

void Flock::push(Program* program)
{
	// generates points
	mVerts[0] = Vert(Vec3(0, 0, .1f), Vec3(0, 0, 1));
	mVerts[1] = Vert(Vec3(-.05f, -.05f, -.1f), glm::normalize(Vec3(-1, -1, -2)));
	mVerts[2] = Vert(Vec3(.05f, -.05f, -.1f), glm::normalize(Vec3(1, -1, -2)));
	mVerts[3] = Vert(Vec3(-.05f, .05f, -.1f), glm::normalize(Vec3(-1, 1, -2)));
	mVerts[4] = Vert(Vec3(.05f, .05f, -.1f), glm::normalize(Vec3(1, 1, -2)));

	// generates indices
	mFaces[0] = Tri(0, 1, 2);
	mFaces[1] = Tri(0, 1, 3);
	mFaces[2] = Tri(0, 2, 4);
	mFaces[3] = Tri(0, 3, 4);
	mFaces[4] = Tri(1, 2, 3);
	mFaces[5] = Tri(2, 3, 4);

	// generates the VAO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// loads data
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, 5 * sizeof(Vert), &mVerts[0], GL_STATIC_DRAW);

	// sets attributes
	glVertexAttribPointer(program->resource(VERT_POSITION), 3, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);
	glVertexAttribPointer(program->resource(VERT_NORMAL), 3, GL_FLOAT, GL_TRUE, sizeof(Vert), (void*)(3 * sizeof(GEfloat)));

	// enables attributes
	glEnableVertexAttribArray(program->resource(VERT_POSITION));
	glEnableVertexAttribArray(program->resource(VERT_NORMAL));
	
	// loads indices
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(Tri), &mFaces[0], GL_STATIC_DRAW);

	// loads instance
	glGenBuffers(1, &mMBO);
	glBindBuffer(GL_ARRAY_BUFFER, mMBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Mat4) * 2 * mCount, NULL, GL_STATIC_DRAW);

	// sets instance attributes
	GEuint model = program->resource("mInstModel");
	GEuint normal = program->resource("mInstNormal");
	glVertexAttribPointer(model + 0, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4) * 2, 0);
	glVertexAttribPointer(model + 1, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4) * 2, (void*)(4 * sizeof(GEfloat)));
	glVertexAttribPointer(model + 2, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4) * 2, (void*)(8 * sizeof(GEfloat)));
	glVertexAttribPointer(model + 3, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4) * 2, (void*)(12 * sizeof(GEfloat)));
	glVertexAttribPointer(normal + 0, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4) * 2, (void*)(16 * sizeof(GEfloat)));
	glVertexAttribPointer(normal + 1, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4) * 2, (void*)(20 * sizeof(GEfloat)));
	glVertexAttribPointer(normal + 2, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4) * 2, (void*)(24 * sizeof(GEfloat)));
	glVertexAttribPointer(normal + 3, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4) * 2, (void*)(28 * sizeof(GEfloat)));

	// enables instance attributes
	glEnableVertexAttribArray(model + 0);
	glEnableVertexAttribArray(model + 1);
	glEnableVertexAttribArray(model + 2);
	glEnableVertexAttribArray(model + 3);
	glEnableVertexAttribArray(normal + 0);
	glEnableVertexAttribArray(normal + 1);
	glEnableVertexAttribArray(normal + 2);
	glEnableVertexAttribArray(normal + 3);

	// sets instance divisor
	glVertexAttribDivisor(model + 0, 1);
	glVertexAttribDivisor(model + 1, 1);
	glVertexAttribDivisor(model + 2, 1);
	glVertexAttribDivisor(model + 3, 1);
	glVertexAttribDivisor(normal + 0, 1);
	glVertexAttribDivisor(normal + 1, 1);
	glVertexAttribDivisor(normal + 2, 1);
	glVertexAttribDivisor(normal + 3, 1);

	// unbinds VAO
	glBindVertexArray(0);
}

void Flock::update(Mat4* viewMatrix, GEdouble elapsed)
{
	// update the position of all of the items
	applyRules(elapsed);

	// initial position
	const Vec3 init = Vec3(0, 0, 1);

	// updates all of the transformation & normal matrices
	for (GEuint i = 0; i < mCount; i++)
	{
		// two matrices
		Mat4 trans = Mat4(1.0f);
		Mat4 norm;

		// calculates the rotation
		Vec3 p = mBoids[i].pos;
		Vec3 v = glm::normalize(mBoids[i].vel);

		// uses look at to orient the boids (easier than calculation direction 
		trans = glm::inverse(glm::lookAt(p, p + v, init));

		// calcualtes normal matrix
		Mat4 modelView = Mat4(*viewMatrix * trans);
		norm = glm::inverseTranspose(modelView);

		// updates them in the array
		mMatrices[i * 2] = trans;
		mMatrices[(i * 2) + 1] = norm;
	}

	// updates instanced matrices in GPU
	glBindBuffer(GL_ARRAY_BUFFER, mMBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Mat4) * 2 * mCount, mMatrices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Flock::render(Program* program)
{
	// draws the elements
	glBindVertexArray(mVAO);
	glDrawElementsInstanced(GL_TRIANGLES, 6*3, GL_UNSIGNED_INT, 0, mCount);
	glBindVertexArray(0);
}