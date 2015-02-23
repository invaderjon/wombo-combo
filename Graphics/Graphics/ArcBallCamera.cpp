#include "ArcBallCamera.h"

using namespace graphics;

ArcBallCamera::ArcBallCamera()
	: Camera(), mInitPos(GE_INVALID_CURSOR), mPrevPos(GE_INVALID_CURSOR), mRotation(), mZoom(0)
{
}

ArcBallCamera::~ArcBallCamera()
{
}

// Camera Position Methods

const Vec3& ArcBallCamera::position() const
{
	return mCenter;
}

void ArcBallCamera::setPosition(const Vec3& position)
{
	mCenter = position;
}

void ArcBallCamera::offsetPosition(const Vec3& offset)
{
	mCenter += offset;
}

void ArcBallCamera::offsetLocalPosition(const Vec3& offset)
{
	mCenter += mRotation * offset;
}

// Camera Radius/Zoom Methods

GEfloat ArcBallCamera::radius() const
{
	// function: r = max(2^(zoom/5), MIN_ZOOM)
	return fmaxf(powf(2, (mZoom / GE_ZOOM_SCALE)), GE_MIN_RADIUS);
}

void ArcBallCamera::setRadius(GEfloat radius)
{
	// radius must be greater than the minimum
	assert(radius > GE_MIN_RADIUS);
	
	// set the calculated zoom
	mZoom = log2f(radius) * GE_ZOOM_SCALE;
}

GEfloat ArcBallCamera::zoom() const
{
	return mZoom;
}

void ArcBallCamera::setZoom(GEfloat zoom)
{
	mZoom = zoom;
	mZoom = fmaxf(mZoom, log2f(GE_MIN_RADIUS) * GE_ZOOM_SCALE);
}

void ArcBallCamera::offsetZoom(GEfloat delta)
{
	mZoom += delta;
	mZoom = fmaxf(mZoom, log2f(GE_MIN_RADIUS) * GE_ZOOM_SCALE);
}



// Camera Rotation Methods

const Quat& ArcBallCamera::rotation() const
{
	return mRotation;
}

void ArcBallCamera::setRotation(const Quat& rotation)
{
	mRotation = rotation;
}

void ArcBallCamera::setRotation(const Mat4& rotation)
{
	mRotation = glm::quat_cast(rotation);
}

void ArcBallCamera::offsetRotation(const Quat& rotation)
{
	mRotation = rotation * mRotation;
}

void ArcBallCamera::offsetRotation(const Mat4& rotation)
{
	mRotation = glm::quat_cast(rotation) * mRotation;
}

void ArcBallCamera::offsetYaw(const GEfloat offset)
{
	mRotation = glm::angleAxis(offset, up()) * mRotation;
}

void ArcBallCamera::offsetPitch(const GEfloat offset)
{
	mRotation = glm::angleAxis(offset, right()) * mRotation;
}

void ArcBallCamera::offsetRoll(const GEfloat offset)
{
	mRotation = glm::angleAxis(offset, forward()) * mRotation;
}

/// <summary>
/// Positions the camera such that it is looking in the specified direction.
/// </summary>
/// <param name="lookAt">The direction to look at.</param>
/// <param name="up">Ignored in calculation and is instead calculated by the arcball's rotation.</param>
void ArcBallCamera::lookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
{
	// sets center and radius
	mCenter = center;
	setRadius(glm::distance(eye, center));
	
	// the position on the sphere
	const Vec3 posOnSphere = eye - center;

	const Vec3 zoom = Vec3(0, 0, radius());
	
	// calculates the rotational axis
	const Vec3 axis = glm::cross(zoom, posOnSphere);

	// calculates the rotation
	const GEfloat len1 = glm::length(zoom);
	const GEfloat len2 = glm::length(posOnSphere);
	const GEfloat lensqr1 = std::powf(len1, 2);
	const GEfloat lensqr2 = std::powf(len2, 2);
	const GEfloat rot = std::sqrtf(lensqr1 * lensqr2) + glm::dot(zoom, posOnSphere);
	
	// creates the quaternion rotation
	mRotation = glm::angleAxis(rot, axis);
}

// Camera Matrices

const Mat4 ArcBallCamera::view() const
{
	return glm::lookAt(eye(), center(), up());
}

// Camera Directional Vectors

const Vec3 ArcBallCamera::eye() const
{
	// returns the sphere location translated by the center
	return (mRotation * Vec3(0, 0, radius())) + mCenter;
}

const Vec3 ArcBallCamera::center() const
{
	return mCenter;
}

const Vec3 ArcBallCamera::up() const
{
	return normalize(mRotation * Vec3(0, 1, 0));
}

const Vec3 ArcBallCamera::forward() const
{
	return normalize(mRotation * Vec3(0, 0, -1));
}

const Vec3 ArcBallCamera::right() const
{
	return normalize(mRotation * Vec3(1, 0, 0));
}

// IControlable Methods

void ArcBallCamera::onClick(int button, int action, int mods)
{
	int down = action != GE_INPUT_ACTION_RELEASE;

	// if the button isn't a middle click ignore it
	if (button != GE_MOUSE_MIDDLE)
		return;

	// if the action is ending then reset motion type and stop processing
	if (!down)
	{
		mMotionType = GE_MOTION_NONE; // reset motion type
		mPrevPos = GE_INVALID_CURSOR; // reset prev cursor
		mInitPos = GE_INVALID_CURSOR; // reset init cursor
		return;
	}

	// if a new action is being taken determine which one
	if (mods & GE_MOD_CTRL) // zoom
	{
		mMotionType = GE_MOTION_ZOOM;
	}
	else if (mods & GE_MOD_SHIFT) // translate
	{
		mMotionType = GE_MOTION_TRANSLATE;
	}
	else // rotate
	{
		mMotionType = GE_MOTION_ROTATE;
	}

	cout << "Motion: " << mMotionType << endl;
}

void ArcBallCamera::onCursorMove(Cursor cursor)
{
	// nothing to do if there's no action being taken
	if (mMotionType == GE_MOTION_NONE)
		return;

	// if this is the first received position, store it and wait for next position
	if (mPrevPos.x == GE_INVALID_CURSOR.x && mPrevPos.y == GE_INVALID_CURSOR.y)
	{
		mInitRotation = mRotation;
		mInitCenter = mCenter;
		mInitPos = cursor;
		mPrevPos = cursor;
		return;
	}

	// we have all the info needed to calculate so continue
	Cursor dp = cursor - mPrevPos;

	// applies transformation based on motion type
	switch (mMotionType)
	{
	case GE_MOTION_ROTATE:
		rotateView(mInitPos, cursor);
		break;
	case GE_MOTION_TRANSLATE:
		translateView(mInitPos, cursor);
		break;
	case GE_MOTION_ZOOM:
		zoomView(dp.y/GE_ZOOM_PIXEL_SCALE);
		break;
	default:
		mInitPos = GE_INVALID_CURSOR;
		mPrevPos = GE_INVALID_CURSOR;
		return;
	}

	// updates the previous position
	mPrevPos = cursor;
}

void ArcBallCamera::onScroll(double xoffset, double yoffset)
{
	// only zoom if not already controlling viewport
	if (mMotionType == GE_MOTION_NONE)
		zoomView(GEfloat(yoffset));
}

// View Controls

void ArcBallCamera::translateView(Cursor init, Cursor term)
{
	// resets position
	setPosition(mInitCenter);

	// calculates movement
	Cursor dp = term - init;

	// scales to screen size
	dp.x /= width();
	dp.y /= height();

	// calculates change in terms of radius
	dp.x *= radius();
	dp.y *= radius();

	// translates the view
	offsetLocalPosition(Vec3(-dp.x, dp.y, 0));
}

void ArcBallCamera::rotateView(Cursor init, Cursor term)
{
	setRotation(mInitRotation);

	// calculates difference
	Cursor dp = term - init;

	// scales to screen size
	dp.x /= width();
	dp.y /= height();

	// calculates rotations
	GEfloat yaw = GEfloat(2*M_PI * dp.x);
	GEfloat pitch = GEfloat(2*M_PI * dp.y);
	
	// rotates the camera
	offsetYaw(-yaw);
	offsetPitch(-pitch);
}

void ArcBallCamera::zoomView(GEfloat delta)
{
	offsetZoom(delta);
}

// Helper Functions

Vec3 ArcBallCamera::getArcBallVector(Cursor curs) const
{
	Vec3 P = Vec3(
		curs.x / width() * 2 - 1.0f,
		curs.y / height() * 2 - 1.0f,
		0);

	P.y = -P.y;
	float OPsquared = P.x * P.x + P.y + P.y;
	if (OPsquared <= 1.0f * 1.0f)
		P.z = sqrtf(1.0f - OPsquared); // pythagorean thm
	else
		P = glm::normalize(P); // nearest point

	P *= radius();

	return P;
}