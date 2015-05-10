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
	return glm::perspectiveFov(mFOV, mWidth, mHeight, mNearPlane, mFarPlane);
}

const Frustum Camera::frustum() const
{
	// gets field of view
	GEfloat fov = FOV();

	// computes near and far distances
	GEfloat near = nearPlane();
	GEfloat far = farPlane();

	// gets aspect ratio
	GEfloat ar = aspectRatio();

	// calculates near and far center points
	Vec3 frwrd = glm::normalize(center() - eye());
	Vec3 nearCenter = eye() + frwrd * near;
	Vec3 farCenter = eye() + frwrd * far;

	// calculates near and far sizes
	GEfloat nearHeight = 2 * std::tanf(fov / 2) * near;
	GEfloat farHeight = 2 * std::tanf(fov / 2) * far;
	GEfloat nearWidth = nearHeight * ar;
	GEfloat farWidth = farHeight * ar;

	// near points
	Vec3 ntl = nearCenter + up() * (nearHeight*0.5f) - right() * (nearWidth*0.5f);
	Vec3 ntr = nearCenter + up() * (nearHeight*0.5f) + right() * (nearWidth*0.5f);
	Vec3 nbl = nearCenter - up() * (nearHeight*0.5f) - right() * (nearWidth*0.5f);
	Vec3 nbr = nearCenter - up() * (nearHeight*0.5f) + right() * (nearWidth*0.5f);

	// far points
	Vec3 ftl = farCenter + up() * (farHeight*0.5f) - right() * (farWidth*0.5f);
	Vec3 ftr = farCenter + up() * (farHeight*0.5f) + right() * (farWidth*0.5f);
	Vec3 fbl = farCenter - up() * (farHeight*0.5f) - right() * (farWidth*0.5f);
	Vec3 fbr = farCenter - up() * (farHeight*0.5f) + right() * (farWidth*0.5f);

	printf("Frustum: <%f, %f, %f> <%f, %f, %f> <%f, %f, %f> <%f, %f, %f>\n", ntl.x, ntl.y, ntl.z, ntr.x, ntr.y, ntr.z, nbl.x, nbl.y, nbl.z, nbr.x, nbr.y, nbr.z);

	// copies to array
	// NTL, NTR, NBL, NBR, FTL, FTR, FBL, FBR
	Vec3 pts[8] = { ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr };

	// creates the frustum from the points
	return Frustum(pts);
}