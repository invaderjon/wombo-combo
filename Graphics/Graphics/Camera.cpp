#include "Camera.h"

using namespace graphics;

Camera::Camera()
	: IControllable()
{
}

Camera::~Camera()
{
}

/// <summary>
/// Gets the cartesian position in 3D space.
/// </summary>
/// <returns>The x, y, z position.</returns>
const Vec3& Camera::position() const
{
	return mPosition;
}

/// <summary>
/// Sets the cartesian position of the camera in 3D space.
/// </summary>
/// <param name="position">The x, y, z position.</param>
void Camera::setPosition(const Vec3& position)
{
	mPosition = position;
}

/// <summary>
/// Translates the camera.
/// </summary>
/// <param name="offset">The offset.</param>
void Camera::offsetPosition(const Vec3& offset)
{
	mPosition += offset;
}

/// <summary>
/// Translates the camera along the local axes. (where x is right, y is forward, and z is up)
/// </summary>
/// <param name="offset">The offset.</param>
void Camera::offsetLocalPosition(const Vec3& offset)
{
	Vec3 localOffset = mRotation * offset;
	mPosition += localOffset;
}

/// <summary>
/// Gets the quaternion representation of the camera's rotation.
/// </summary>
/// <returns>The rotational quaternion.</returns>
const Quat& Camera::rotation() const
{
	return mRotation;
}

/// <summary>
/// Sets the rotation using the quaternion representation.
/// </summary>
/// <param name="rotation">The rotation.</param>
void Camera::setRotation(const Quat& rotation)
{
	mRotation = glm::normalize(rotation);
}

/// <summary>
/// Sets the rotation using a rotational matrix.
/// </summary>
/// <param name="rotation">The rotational matrix.</param>
void Camera::setRotation(const Mat4& rotation)
{
	mRotation = Quat(glm::normalize(glm::quat_cast(rotation)));
}

/// <summary>
/// Offsets the rotation using a quaternion rotation.
/// </summary>
/// <param name="rotation">The offset rotation.</param>
void Camera::offsetRotation(const Quat& rotation)
{
	mRotation = glm::normalize(rotation * mRotation);
}

/// <summary>
/// Offsets the rotation using a rotational matrix.
/// </summary>
/// <param name="rotation">The rotational matrix.</param>
void Camera::offsetRotation(const Mat4& rotation)
{
	mRotation = glm::normalize(glm::quat_cast(rotation) * mRotation);
}

/// <summary>
/// Offsets the yaw.
/// </summary>
/// <param name="offset">The rotation about the up vector.</param>
void Camera::offsetYaw(GEfloat offset)
{
	// creates a quaternion for the rotation
	Quat yawQuat = glm::angleAxis(offset, up());

	// offsets the rotation by the quaternion
	offsetRotation(yawQuat);
}

/// <summary>
/// Offsets the pitch.
/// </summary>
/// <param name="offset">The rotation about the right vector.</param>
void Camera::offsetPitch(GEfloat offset)
{
	// creates a quaternion for the rotation
	Quat pitchQuat = glm::angleAxis(offset, right());

	// offsets the rotation by the quaternion
	offsetRotation(pitchQuat);
}

/// <summary>
/// Offsets the roll.
/// </summary>
/// <param name="offset">The rotation about the forward vector.</param>
void Camera::offsetRoll(GEfloat offset)
{
	// creates a quaternion for the rotation
	Quat rollQuat = glm::angleAxis(offset, forward());

	// offsets the rotation by the quaternion
	offsetRotation(rollQuat);
}

/// <summary>
/// Rotates about the global X axis.
/// </summary>
/// <param name="offset">The rotation about the global X axis.</param>
void Camera::offsetXRot(GEfloat offset)
{
	// rotates around the global x axis
	Quat xQuat = glm::angleAxis(offset, Vec3(1, 0, 0));

	// offsets the rotation by the quaternion
	offsetRotation(xQuat);
}

/// <summary>
/// Rotates about the global Y axis.
/// </summary>
/// <param name="offset">The rotation about the global Y axis.</param>
void Camera::offsetYRot(GEfloat offset)
{
	// rotates around the global y axis
	Quat yQuat = glm::angleAxis(offset, Vec3(0, 1, 0));

	// offsets the rotation by the quaternion
	offsetRotation(yQuat);
}

/// <summary>
/// Rotates about the global Z axis.
/// </summary>
/// <param name="offset">The rotation about the global Z axis.</param>
void Camera::offsetZRot(GEfloat offset)
{
	// rotates around the global x axis
	Quat zQuat = glm::angleAxis(offset, Vec3(0, 0, 1));

	// offsets the rotation by the quaternion
	offsetRotation(zQuat);
}

/// <summary>
/// Positions the camera such that it is looking in the specified direction.
/// </summary>
/// <param name="lookAt">The direction to look at.</param>
/// <param name="up">The upward direction in the viewport.</param>
void Camera::lookAt(Vec3 lookAt, Vec3 up)
{
	Vec3 forward = glm::normalize(lookAt);
	up = glm::normalize(up);
	
	mRotation = glm::normalize(glm::quat_cast(glm::lookAt(Vec3(0, 0, 0), forward, up)));
	
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

/// <summary>
/// Gets the matrix transformation for the camera.
/// </summary>
/// <returns></returns>
Mat4 Camera::matrix() const
{
	return projection() * view();
}

/// <summary>
/// Gets the projection matrix for the camera.
/// </summary>
/// <returns>The projection matrix.</returns>
Mat4 Camera::projection() const
{
	return glm::perspective(mFOV, aspectRatio(), mNearPlane, mFarPlane);
}

/// <summary>
/// Gets the combined rotation and translation matrix.
/// </summary>
/// <returns>The view matrix.</returns>
Mat4 Camera::view() const
{
	//cout << "Position: " << mPosition.x << ", " << mPosition.y << ", " << mPosition.z << endl;
	return glm::translate(orientation(), -mPosition);
}

/// <summary>
/// Gets the rotation matrix for the camera.
/// </summary>
/// <returns>The rotational matrix.</returns>
Mat4 Camera::orientation() const
{
	Quat rot = mRotation;
	rot = glm::inverse(rot);
	//cout << "Rot: " << rot.x << ", " << rot.y << ", " << rot.z << ", " << rot.w << endl;
	return glm::mat4_cast(rot);
}

/// <summary>
/// Gets the forward vector for the camera.
/// </summary>
/// <returns>The local y axis direction.</returns>
Vec3 Camera::forward() const
{
	return mRotation * Vec3(0, 1, 0);
}

/// <summary>
/// Gets the up vector for the camera.
/// </summary>
/// <returns>The local z axis direction.</returns>
Vec3 Camera::up() const
{
	return mRotation * Vec3(0, 0, 1);
}

/// <summary>
/// Gets the right vector for the camera.
/// </summary>
/// <returns>The local x axis direction.</returns>
Vec3 Camera::right() const
{
	return mRotation * Vec3(1, 0, 0);
}