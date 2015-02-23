#include "Camera.h"

using namespace graphics;

Camera::Camera()
	: IControllable(), mNearPlane(0.001f), mFarPlane(100.0f), mFOV(45.0f), mDOF(100)
{
}

Camera::~Camera()
{
}

/// <summary>
/// Gets the field of view.
/// </summary>
/// <returns>The FoV.</returns>
GEfloat Camera::FOV() const
{
	return mFOV;
}

/// <summary>
/// Sets the field of view.
/// </summary>
/// <param name="FOV">The FoV.</param>
void Camera::setFOV(GEfloat FOV)
{
	mFOV = FOV;
}

/// <summary>
/// Gets the depth of field.
/// </summary>
/// <returns>The DoF</returns>
GEfloat Camera::DOF() const
{
	return mDOF;
}

/// <summary>
/// Sets the depth of field.
/// </summary>
/// <param name="DOF">The DoF.</param>
void Camera::setDOF(GEfloat DOF)
{
	mDOF = DOF;
}

/// <summary>
/// Gets the aspect ratio.
/// </summary>
/// <returns>The aspect ratio.</returns>
GEfloat Camera::aspectRatio() const
{
	return (mHeight > 0) ? mWidth / mHeight : 0.00001f;
}

/// <summary>
/// Gets the viewport width.
/// </summary>
/// <returns>The display width.</returns>
GEfloat Camera::width() const
{
	return mWidth;
}

/// <summary>
/// Gets the viewport height.
/// </summary>
/// <returns>The display height.</returns>
GEfloat Camera::height() const
{
	return mHeight;
}

/// <summary>
/// Sets the viewport size.
/// </summary>
/// <param name="width">The display width.</param>
/// <param name="height">The display height.</param>
void Camera::setSize(GEfloat width, GEfloat height)
{
	//assert(width > 0);
	//assert(height > 0);
	mWidth = width;
	mHeight = height;
}

/// <summary>
/// Gets the near clip plane.
/// </summary>
/// <returns>The nearest visible distance.</returns>
GEfloat Camera::nearPlane() const
{
	return mNearPlane;
}

/// <summary>
/// Gets the far clip plane.
/// </summary>
/// <returns>The farthest visible distance.</returns>
GEfloat Camera::farPlane() const
{
	return mFarPlane;
}

/// <summary>
/// Sets the near and far planes, where near > 0 and far > near.
/// </summary>
/// <param name="near">The near clip distance.</param>
/// <param name="far">The far clip distance.</param>
void Camera::setNearAndFarPlanes(GEfloat near, GEfloat far)
{
	assert(near > GEfloat(0.0f));
	assert(far > near);
	mNearPlane = near;
	mFarPlane = far;
}

const Mat4 Camera::matrix() const
{
	return projection() * view();
}

const Mat4 Camera::projection() const
{
	return glm::perspectiveFov(mFOV, mWidth, mHeight, mNearPlane, mFarPlane) * view();
}