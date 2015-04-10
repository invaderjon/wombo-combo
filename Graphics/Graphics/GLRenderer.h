#pragma once
#include "IRenderer.h"

namespace graphics
{
	class GLRenderer :
		public IRenderer
	{
	public:
		GLRenderer();
		~GLRenderer();

		void prepare();
		void destroy();
		
		void render(const RenderInfo& info);
	};
}