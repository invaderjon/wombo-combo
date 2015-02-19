#pragma once

#include "Input.h"

namespace graphics
{
	class IControllable
	{
	public:
		virtual void onCursorMove(Cursor cursor) { }
		virtual void onClick(int button, int action, int mods) { }
		virtual void onInput(int key, int action, int mods) { }
		virtual void onScroll(double xoffset, double yoffset) { }
	};
}