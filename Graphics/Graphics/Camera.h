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
		const Vec3& position() const;
		void setPosition(const Vec3& position);		
		void offsetPosition(const Vec3& offset);
		void offsetLocalPosition(const Vec3& offset);

		// rotation methods
		const Quat& rotation() const;
		inline void setRotation(const Quat& rotation); // set the rotation about an arbitrary axis
		inline void setRotation(const Mat4& rotation); // sets the rotation from a given rotational matrix
		inline void offsetRotation(const Quat& rotation); // offsets the rotation about an arbitrary axis
		inline void offsetRotation(const Mat4& rotation); // offsets the rotation using a rotational matrix
		virtual void offsetYaw(GEfloat offset); // local yaw [around up vector]
		virtual void offsetPitch(GEfloat offset); // local pitch [around right vector]
		virtual void offsetRoll(GEfloat offset); // local roll [around forward vector]
		virtual void offsetXRot(GEfloat offset); // global rotation around x axis
		virtual void offsetYRot(GEfloat offset); // global rotation around y axis
		virtual void offsetZRot(GEfloat offset); // global rotation around z axis
		virtual void lookAt(Vec3 lookAt, Vec3 up); // orients the camera to look in the given direction
		
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
		Mat4 matrix() const;

		// The projection perspective matrix
		Mat4 projection() const;

		// the combined translation and rotation matrix
		Mat4 view() const;
		
		// Rotation matrix that determines where the camera is looking.
		Mat4 orientation() const;

		// local axes
		virtual Vec3 eye() const;
		virtual Vec3 center() const;
		virtual Vec3 forward() const;
		virtual Vec3 up() const; 
		virtual Vec3 right() const;
	private:
		Vec3 mPosition; // cartensian position in 3D space
		Quat mRotation; // the orienation vector
		GEfloat mNearPlane; // closes visible content
		GEfloat mFarPlane; // farthest visible content
		GEfloat mFOV; // field of view
		GEfloat mDOF; // depth of field
		GEfloat mWidth; // viewport width
		GEfloat mHeight; // Viewport height
	};
}