#pragma once
#include "IEngine.h"

// will handle meshes, lighting, cameras, and rendering

namespace graphics
{
	class GraphicsEngine :
		public IEngine
	{
	public:
		GraphicsEngine();
		~GraphicsEngine();

		void startup();
		void shutdown();
	};
}
