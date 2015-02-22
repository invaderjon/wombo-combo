#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "Camera.h"
#include "Input.h"

#define SCROLL_SCALE GEfloat(100.0f)
#define MOTION_NONE 0
#define MOTION_ROTATE 1
#define MOTION_TRANSLATE 2
#define INVALID_CURSOR Cursor(-1, -1)

using namespace std;

namespace graphics
{
	class ArcBallCamera :
		public Camera
	{
	public:
		ArcBallCamera();
		~ArcBallCamera();
		void onCursorMove(Cursor cursor);
		void onClick(int button, int action, int mods);
		void onScroll(double xoffset, double yoffset);
	private:
		int mMotionType;
		Cursor mPrevPos;
	};
}
