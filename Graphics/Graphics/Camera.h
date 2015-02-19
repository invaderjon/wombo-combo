#pragma once

#include "Graphics.h"
#include "IControllable.h"

//
// Title: Camera
// Author: Jonathan DiGiacomo
// Version: 1.0.0
//
// Provides a base list of methods used by all cameras to orient themselves.
//

namespace graphics
{
	class Camera :
		public IControllable
	{
	public:
		Camera();
		~Camera();

		// position methods
		const Vec3& position() const;
		void setPosition(const Vec3& position);
		void offsetPosition(const Vec3& offset);

		// field of view (zoom)
		GEfloat FOV() const;
		void setFOV(GEfloat FOV);

		// depth of field (focus) (unused in rendering)
		GEfloat DOF() const;
		void setDOF(GEfloat DOF);
			
		// The closes visible distance from the camera.
		// Must be greater than zero.
		GEfloat nearPlane() const;

		// The farthest visible distance from the camera.
		// Must be greater than nearPlane
		GEfloat farPlane() const;

		// Sets the clipping planes
		void setNearAndFarPlanes(GEfloat near, GEfloat far);
		
		// Rotation matrix that determines where the camera is looking.
		Mat4 orientation() const;

		void offsetOrientation(float upAngle, float rightAngle);
	private:
		Vec3 mPosition; // cartensian position in 3D space
		Vec3 mLookAt; // look at direction
		Vec3 mUp; // up unit vector
		GEfloat mFOV; // field of view
		GEfloat mDOF; // depth of field
		GEfloat mNearPlane; // closes visible content
		GEfloat mFarPlane; // farthest visible content
	};
}