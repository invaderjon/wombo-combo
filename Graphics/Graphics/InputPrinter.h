#pragma once

#include <stdio.h>
#include "Platform.h"
#include "IControllable.h"

using namespace std;

namespace graphics
{
	class InputPrinter :
		public IControllable
	{
	public:
		InputPrinter();
		~InputPrinter();
		virtual void onCursorMove(Cursor cursor);
		virtual void onClick(int button, int action, int mods);
		virtual void onInput(int key, int action, int mods);
		virtual void onScroll(double xoffset, double yoffset);
	};
}

