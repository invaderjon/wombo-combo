#include "ParticleRenderer.h"

using namespace graphics;

ParticleRenderer::ParticleRenderer(const ParticleData& data, string texture)
	: mData(data), mTex(texture, GL_CLAMP, 0)
{
	mQuad[0] = Vec3(-0.5f, -0.5f, 0);
	mQuad[1] = Vec3(-0.5f, 0.5f, 0);
	mQuad[2] = Vec3(0.5f, -0.5f, 0);
	mQuad[3] = Vec3(0.5f, 0.5f, 0);
	mFaces[0].a = 0;
	mFaces[0].b = 1;
	mFaces[0].c = 2;
	mFaces[1].a = 3;
	mFaces[1].b = 1;
	mFaces[1].c = 2;
}

ParticleRenderer::~ParticleRenderer()
{
}

void ParticleRenderer::push(Program* program)
{
	// gen and bind VAO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// gen vertex buffer
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * 6, &mQuad[0], GL_STATIC_DRAW);

	// sets attributes
	glVertexAttribPointer(program->resource(VERT_POSITION), 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), 0);
	
	// enables attributes
	glEnableVertexAttribArray(program->resource(VERT_POSITION));

	// loads indices
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(Tri), &mFaces[0], GL_STATIC_DRAW);

	// gen instance buffer 
	glGenBuffers(1, &mMBO);
	glBindBuffer(GL_ARRAY_BUFFER, mMBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleData::Particle) * mData.count(), NULL, GL_STATIC_DRAW);

	// configures instance attributes
	glVertexAttribPointer(program->resource("vInstPos"), 3, GL_FLOAT, GL_FALSE, sizeof(ParticleData::Particle), 0);
	glVertexAttribPointer(program->resource("vInstCol"), 4, GL_FLOAT, GL_FALSE, sizeof(ParticleData::Particle), (void*)(9 * sizeof(GEfloat)));
	glVertexAttribPointer(program->resource("vInstSize"), 1, GL_FLOAT, GL_FALSE, sizeof(ParticleData::Particle), (void*)(15 * sizeof(GEfloat)));

	// enables instance attributes
	glEnableVertexAttribArray(program->resource("vInstPos"));
	glEnableVertexAttribArray(program->resource("vInstCol"));
	glEnableVertexAttribArray(program->resource("vInstSize"));

	// sets instance divisor
	glVertexAttribDivisor(program->resource("vInstPos"), 1);
	glVertexAttribDivisor(program->resource("vInstCol"), 1);
	glVertexAttribDivisor(program->resource("vInstSize"), 1);
	
	// unbinds VAO
	glBindVertexArray(0);

}

void ParticleRenderer::update(Mat4* viewMatrix, GEdouble elapsed)
{
	// if no particles are alive then skip
	if (mData.alive() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mMBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(ParticleData::Particle) * mData.alive(), &mData[0]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void ParticleRenderer::render(Program* program)
{
	// determines if is blending
	if (mData.srcFunc() != GL_ONE || mData.dstFunc() != GL_ZERO)
	{
		// enables blending
		//glEnable(GL_BLEND);
		//glBlendFunc(mData.srcFunc(), mData.dstFunc());
	}
	else // blending modes have no impact, so disable
		glDisable(GL_BLEND);

	// sets texture uniform
	glUniform1i(program->resource("tex"), mTex.id());

	// binds texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTex.handle());

	//glUniformMatrix4fv(program->resource(MAT_MODEL), 1, GL_FALSE, glm::value_ptr(Mat4()));

	// renders particles
	glBindVertexArray(mVAO);
	glDrawElementsInstanced(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, 0, mData.alive());
	glBindVertexArray(0);

	glDisable(GL_BLEND);
}