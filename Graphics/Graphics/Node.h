#pragma once

#include "IIdentifiable.h"
#include "Primitives.h"

// Base class which defines anything that interacts 
// or is contained within the world.

namespace graphics
{
	class Node
		: public IIdentifiable
	{
	public:
		Node();
		~Node();
	};
}