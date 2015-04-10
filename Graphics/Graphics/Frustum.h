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
	};

}