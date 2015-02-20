#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Camera.h"
#include "Input.h"

#define MOTION_NONE 0
#define MOTION_ROTATE 1
#define MOTION_TRANSLATE 2
#define INVALID_CURSOR Cursor(-1, -1)

namespace graphics
{
	class ArcBallCamera :
		public Camera
	{
	public:
		ArcBallCamera();
		~ArcBallCamera();
		virtual void onCursorMove(Cursor cursor);
		virtual void onClick(int button, int action, int mods);
	private:
		int mMotionType;
		Cursor mPrevPos;
	};
}
