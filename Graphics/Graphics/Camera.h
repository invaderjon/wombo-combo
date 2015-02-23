#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "Graphics.h"
#include "IControllable.h"

//
// Title: Camera
// Author: Jonathan DiGiacomo
// Version: 1.0.0
//
// Provides a base list of methods used by all cameras to orient themselves.
//

using namespace std;

namespace graphics
{
	class Camera :
		public IControllable
	{
	public:
		Camera();
		~Camera();

		//
		// position methods
		//
		/// <summary>
		/// Gets the cartesian position in 3D space.
		/// </summary>
		/// <returns>The x, y, z position.</returns>
		virtual const Vec3& position() const = 0;

		/// <summary>
		/// Sets the cartesian position of the camera in 3D space.
		/// </summary>
		/// <param name="position">The x, y, z position.</param>
		virtual void setPosition(const Vec3& position) = 0;

		/// <summary>
		/// Translates the camera.
		/// </summary>
		/// <param name="offset">The offset.</param>
		virtual void offsetPosition(const Vec3& offset) = 0;

		/// <summary>
		/// Translates the camera along the local axes. (where x is right, y is forward, and z is up)
		/// </summary>
		/// <param name="offset">The offset.</param>
		virtual void offsetLocalPosition(const Vec3& offset) = 0;

		// rotation methods
		/// <summary>
		/// Gets the quaternion representation of the camera's rotation.
		/// </summary>
		/// <returns>The rotational quaternion.</returns>
		virtual const Quat& rotation() const = 0;

		/// <summary>
		/// Sets the rotation using the quaternion representation.
		/// </summary>
		/// <param name="rotation">The rotation.</param>
		virtual void setRotation(const Quat& rotation) = 0; // set the rotation about an arbitrary axis
		
		/// <summary>
		/// Sets the rotation using a rotational matrix.
		/// </summary>
		/// <param name="rotation">The rotational matrix.</param>
		virtual void setRotation(const Mat4& rotation) = 0; // sets the rotation from a given rotational matrix
		
		/// <summary>
		/// Offsets the rotation using a quaternion rotation.
		/// </summary>
		/// <param name="rotation">The offset rotation.</param>
		virtual void offsetRotation(const Quat& rotation) = 0; // offsets the rotation about an arbitrary axis
		
		/// <summary>
		/// Offsets the rotation using a rotational matrix.
		/// </summary>
		/// <param name="rotation">The rotational matrix.</param>
		virtual void offsetRotation(const Mat4& rotation) = 0; // offsets the rotation using a rotational matrix
		
		/// <summary>
		/// Offsets the yaw.
		/// </summary>
		/// <param name="offset">The rotation about the up vector.</param>
		virtual void offsetYaw(const GEfloat offset) = 0; // local yaw [around up vector]
		
		/// <summary>
		/// Offsets the pitch.
		/// </summary>
		/// <param name="offset">The rotation about the right vector.</param>
		virtual void offsetPitch(const GEfloat offset) = 0; // local pitch [around right vector]
		
		/// <summary>
		/// Offsets the roll.
		/// </summary>
		/// <param name="offset">The rotation about the forward vector.</param>
		virtual void offsetRoll(const GEfloat offset) = 0; // local roll [around forward vector]
		
		/// <summary>
		/// Positions the camera such that it is looking in the specified direction.
		/// </summary>
		/// <param name="lookAt">The direction to look at.</param>
		/// <param name="up">The upward direction in the viewport.</param>
		virtual void lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) = 0; // orients the camera to look in the given direction
		
		// field of view (zoom)
		GEfloat FOV() const;
		void setFOV(GEfloat FOV);

		// depth of field (focus) (unused in rendering until further notice)
		GEfloat DOF() const;
		void setDOF(GEfloat DOF);

		// the aspect ratio
		GEfloat aspectRatio() const;
		GEfloat width() const;
		GEfloat height() const;
		void setSize(GEfloat width, GEfloat height);

		// The closes visible distance from the camera.
		// Must be greater than zero.
		GEfloat nearPlane() const;

		// The farthest visible distance from the camera.
		// Must be greater than nearPlane
		GEfloat farPlane() const;

		// Sets the clipping planes
		void setNearAndFarPlanes(GEfloat near, GEfloat far);
		
		// The combined projection and view matrix
		/// <summary>
		/// Gets the matrix transformation for the camera.
		/// </summary>
		/// <returns></returns>
		virtual const Mat4 matrix() const;

		// The projection perspective matrix
		/// <summary>
		/// Gets the projection matrix for the camera.
		/// </summary>
		/// <returns>The projection matrix.</returns>
		virtual const Mat4 projection() const;

		// the combined translation and rotation matrix
		/// <summary>
		/// Gets the combined rotation and translation matrix.
		/// </summary>
		/// <returns>The view matrix.</returns>
		virtual const Mat4 view() const = 0;

		// local axes
		/// <summary>
		/// Gets the eye position vector for the camera.
		/// </summary>
		/// <returns>The eye vector.</returns>
		virtual const Vec3 eye() const = 0;

		/// <summary>
		/// Gets the center position vector for the camera.
		/// </summary>
		/// <returns>The camera view center.</returns>
		virtual const Vec3 center() const = 0;

		/// <summary>
		/// Gets the forward vector for the camera.
		/// </summary>
		/// <returns>The camera view forward vector (untranslated).</returns>
		virtual const Vec3 forward() const = 0;

		/// <summary>
		/// Gets the up vector for the camera.
		/// </summary>
		/// <returns>The local z axis vector (untranslated).</returns>
		virtual const Vec3 up() const = 0;

		/// <summary>
		/// Gets the right vector for the camera.
		/// </summary>
		/// <returns>The local x axis vector (untranslated).</returns>
		virtual const Vec3 right() const = 0;
	private:
		//Vec3 mPosition; // cartensian position in 3D space
		//Quat mRotation; // the orienation vector
		GEfloat mNearPlane; // closes visible content
		GEfloat mFarPlane; // farthest visible content
		GEfloat mFOV; // field of view
		GEfloat mDOF; // depth of field
		GEfloat mWidth; // viewport width
		GEfloat mHeight; // Viewport height
	};
}