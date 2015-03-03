#pragma once

#include "Primitives.h"

// Base class which defines anything that interacts 
// or is contained within the world.

namespace graphics
{
	class Node
	{
	private:
		// global
		static GEuint sCurId;
		static GEuint nextId();

		// instance
		// unique id
		GEuint mId;

	public:
		Node();
		~Node();

		// get unique id
		inline GEuint id()	const;
	};
}