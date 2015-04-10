#pragma once
#include "IGear.h"

namespace graphics
{
	typedef struct	sRenderInfo
	{
		// stuff needed for rendering goes in here
	}				RenderInfo;

	class IRenderer :
		public IGear
	{
	public:
		virtual void render(const RenderInfo& info) = 0;
	};
}
