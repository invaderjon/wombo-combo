#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "Camera.h"
#include "Input.h"

#define GE_MIN_RADIUS GEfloat(0.0001f) // max zoom in req is 50
#define GE_ZOOM_SCALE GEfloat(5.0f)
#define GE_ZOOM_PIXEL_SCALE GEfloat(4.0f)
#define GE_MOTION_NONE 0
#define GE_MOTION_ROTATE 1
#define GE_MOTION_TRANSLATE 2
#define GE_MOTION_ZOOM 3
#define GE_INVALID_CURSOR Cursor(-1, -1)

using namespace std;

namespace graphics
{
	class ArcBallCamera :
		public Camera
	{
	public:
		ArcBallCamera();
		~ArcBallCamera();
		
		// translation methods
		const Vec3& position() const;
		void setPosition(const Vec3& position);
		void offsetPosition(const Vec3& offset);
		void offsetLocalPosition(const Vec3& offset);

		// radius/zoom
		GEfloat radius() const;
		void setRadius(GEfloat radius); // determines zoom from given radius
		GEfloat zoom() const;
		void setZoom(GEfloat zoom); // sets the zoom value
		void offsetZoom(GEfloat delta); // offsets the zoom by a given amount

		// rotation methods
		const Quat& rotation() const;
		void setRotation(const Quat& rotation);
		void setRotation(const Mat4& rotation);
		void offsetRotation(const Quat& rotation);
		void offsetRotation(const Mat4& rotation);
		void offsetYaw(const GEfloat offset);
		void offsetPitch(const GEfloat offset);
		void offsetRoll(const GEfloat offset);
		void lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

		// gl matrices
		const Mat4 view() const;
		
		// camera vectors
		// lookat/directions
		const Vec3 eye() const;
		const Vec3 center() const;
		const Vec3 up() const;
		const Vec3 forward() const;
		const Vec3 right() const;

		// controllables
		void onCursorMove(Cursor cursor);
		void onClick(int button, int action, int mods);
		void onScroll(double xoffset, double yoffset);

	private:
		// camera controls
		void translateView(Cursor init, Cursor term);
		void rotateView(Cursor init, Cursor term);
		void zoomView(GEfloat delta);

		// helper functions
		Vec3 getArcBallVector(Cursor curs) const;

		GEfloat mZoom;   // used to calculate radius
		Quat mRotation;  // rotation
		Vec3 mCenter;    // translation
		int mMotionType;
		Quat mInitRotation; // initial rotation
		Vec3 mInitCenter; // initial translation
		Cursor mInitPos; // initial cusor pos
		Cursor mPrevPos; // previous cursor pos
	};
}
