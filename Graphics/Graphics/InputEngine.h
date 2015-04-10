#pragma once
#include "IEngine.h"

// recognizes devices, receives and parses input, broadcasts parsed input
// closer to a subsystem but is easier to define as complete system

namespace graphics
{
	class InputEngine :
		public IEngine
	{
	public:
		InputEngine();
		~InputEngine();

		void startup();
		void shutdown();
	};
}