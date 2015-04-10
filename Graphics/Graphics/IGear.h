#pragma once
namespace graphics
{
	class IGear
	{
	public:
		virtual void prepare() = 0;
		virtual void destroy() = 0;
	};
}
