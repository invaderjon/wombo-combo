#pragma once
#include "Buffers.h"
#include "Graphics.h"
#include "Program.h"
#include "IRenderable.h"


namespace graphics
{

	class ISphere :
		public IRenderable
	{
	public:
		virtual GEfloat radius() const = 0;
	};

}