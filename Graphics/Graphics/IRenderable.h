#pragma once

#include <glm/gtc/type_ptr.hpp>
#include "Primitives.h"
#include "ShaderStructs.h"
#include "Program.h"

namespace graphics
{
	class IRenderable
	{
	public:
		virtual void push(Program* program) = 0;
		virtual void update(Mat4* viewMatrix, GEdouble elapsed) = 0;
		virtual void render(Program* program) = 0;
	protected:
		GEuint mVAO;
		GEuint mVBO;
		GEuint mIBO;
		Mat4 mModelMatrix;
		Mat3 mNormalMatrix;
	};
}
