#pragma once
#include "Node.h"

// Defines anything that can be placed within the world

namespace graphics
{
	class Entity :
		public Node
	{
	public:
		Entity();
		~Entity();
	};
}