#pragma once

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include "IRenderable.h"
#include "ParticleData.h"
#include "Texture.h"

namespace graphics
{

	class ParticleRenderer
		: public IRenderable
	{
	public:
		ParticleRenderer(const ParticleData& data, string texture);
		~ParticleRenderer();

		// render functions
		void push(Program* program);
		void update(Mat4* viewMatrix, GEdouble elapsed); // does nothing
		void render(Program* program);
	private:
		const ParticleData& mData;
		Vec3 mQuad[4];
		Tri mFaces[2];
		GEuint mMBO;
		Texture mTex;
	};

}

