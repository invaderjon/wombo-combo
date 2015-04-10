#pragma once
#include "IEngine.h"

// will handle collision, motion, forces, and particle systems [only collision and motion will be implemented for now]

namespace graphics
{
	class PhysicsEngine :
		public IEngine
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();

		void startup();
		void shutdown();
	};
}
