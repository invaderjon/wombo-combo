#pragma once
#include "IRenderable.h"
#include "Plane.h"
#include "Sphere.h"

namespace graphics
{

	class Frustum
	{
	private:
		// left, right, top, bottom, far, near
		Plane mBounds[6];
	public:
		Frustum();
		// Verts of the frustum arranged as such:
		// NTL, NTR, NBL, NBR, FTL, FTR, FBL, FBR
		// NOTE: there must be exactly 8 vertices
		Frustum(Vec3* verts);
		// Planes of the frustum arranged as such:
		// L, R, T, B, F, N
		// NOTE: there must be exactly 6 planes
		Frustum(Plane* planes);
		// Destructor
		~Frustum();
		
		// checks if the frustum contains a cube
		bool contains(const Vec4& cube) const;

		// checks if the frustum contains a point
		bool contains(const Vec3& pt) const;
	};
}