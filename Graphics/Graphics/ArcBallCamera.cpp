#include "ArcBallCamera.h"

using namespace graphics;

ArcBallCamera::ArcBallCamera()
	: Camera()
{
}

ArcBallCamera::~ArcBallCamera()
{
}

void ArcBallCamera::onClick(int button, int action, int mods)
{
	int down = action != GE_INPUT_ACTION_RELEASE;
	switch (button)
	{
	case GE_MOUSE_LEFT:
		if (down)
			mMotionType = MOTION_ROTATE;
		else
			mMotionType = MOTION_NONE;
		break;
	case GE_MOUSE_MIDDLE:
		if (down)
			mMotionType = MOTION_TRANSLATE;
		else
			mMotionType = MOTION_NONE;
		break;
	default:
		mMotionType = MOTION_NONE;
	}

	// if motion type is now none reset cursor
	if (mMotionType == MOTION_NONE)
		mPrevPos = INVALID_CURSOR;

	cout << "Motion: " << mMotionType << endl;
}

void ArcBallCamera::onCursorMove(Cursor cursor)
{
	// nothing to do if there's no action being taken
	if (mMotionType == MOTION_NONE)
		return;
	// if this is the first received position, store it and wait for next position
	if (mPrevPos.x == INVALID_CURSOR.x && mPrevPos.y == INVALID_CURSOR.y)
	{
		mPrevPos = cursor;
		return;
	}

	// we have all the info needed to calculate so continue
	Cursor dp = cursor - mPrevPos;

	// applies transformation based on motion type
	switch (mMotionType)
	{
	case MOTION_ROTATE:
	{
		// converts the distance in pixels to radians
		GEfloat yaw = GEfloat((dp.x / width()) * M_PI_2);
		GEfloat pitch = GEfloat((dp.y / height()) * M_PI_2);

		// applies to rotations
		offsetPitch(pitch);
		offsetYaw(yaw);
	}
		break;
	case MOTION_TRANSLATE:
	{
		// converts to translation (0 to 1)
		GEfloat dx = GEfloat(dp.x / width());
		GEfloat dz = GEfloat(dp.y / height());

		// translates using the local axis
		offsetLocalPosition(Vec3(dx, dz, 0));
	}
		break;
	default:
		mPrevPos = INVALID_CURSOR;
		return;
	}

	// updates the previous position
	mPrevPos = cursor;
}

void ArcBallCamera::onScroll(double xoffset, double yoffset)
{
	GEfloat dy = GEfloat(yoffset) / SCROLL_SCALE;
	offsetLocalPosition(Vec3(0, 0, dy));
}