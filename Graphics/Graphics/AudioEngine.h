#pragma once
#include "IEngine.h"

// unimplemented as it is unnecessary at this point in time

namespace graphics
{
	class AudioEngine :
		public IEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void startup();
		void shutdown();
	};
}
