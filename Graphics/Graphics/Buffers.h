#pragma once

#include "Primitives.h"

namespace graphics
{
	class Buffers
	{
	public:
		static GEuint nextBuffer();
	private:
		static GEuint sNextBuf;
	};
}

