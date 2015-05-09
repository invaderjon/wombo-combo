#pragma once
#include "IRenderable.h"
namespace graphics
{

	class Frustum :
		public IRenderable
	{
	public:
		Frustum();
		~Frustum();

		bool contains(const Vec4& cube) const;
	};

}