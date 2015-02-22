#pragma once

#include <glm/gtc/type_ptr.hpp>
#include "Primitives.h"
#include "ShaderStructs.h"

namespace graphics
{
	class IRenderable
	{
	public:
		virtual void push(Attributes& attr) = 0;
		virtual void update(Mat4* viewMatrix) = 0;
		virtual void render(ShaderIndices* indices) = 0;
	protected:
		GEuint mVAO;
		GEuint mVBO;
		GEuint mIBO;
		Material mMaterial;
		Mat4 mModelMatrix;
		Mat3 mNormalMatrix;
	};
}
