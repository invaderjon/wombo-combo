#pragma once
#include "Entity.h"

// anything with a mesh

namespace graphics
{
	class Object :
		public Entity
	{
	public:
		Object();
		~Object();
	};
}