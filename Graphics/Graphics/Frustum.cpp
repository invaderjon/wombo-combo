#include "Frustum.h"

using namespace graphics;

Frustum::Frustum()
{
}

Frustum::Frustum(Vec3* verts)
{
	// NTL, NTR, NBL, NBR, FTL, FTR, FBL, FBR 
	// L, R, T, B, F, N
	// all constructed CCW
	mBounds[0] = Plane(verts[3], verts[2], verts[6]);
	mBounds[1] = Plane(verts[1], verts[3], verts[7]);
	mBounds[2] = Plane(verts[1], verts[0], verts[4]);
	mBounds[3] = Plane(verts[2], verts[3], verts[6]);
	mBounds[4] = Plane(verts[6], verts[7], verts[5]);
	mBounds[5] = Plane(verts[0], verts[1], verts[3]);
}

Frustum::Frustum(Plane* planes)
{
	// copies the planes
	for (int i = 0; i < 6; ++i)
		mBounds[i] = planes[i];
}

Frustum::~Frustum()
{
}

bool Frustum::contains(const Vec4& cube) const
{
	bool cont = false;
	GEfloat x = cube.x;
	GEfloat y = cube.y;
	GEfloat z = cube.z;
	GEfloat s = cube.s;

	// checks if it's contained for each point
	cont |= contains(Vec3(x - s, y - s, z - s));
	cont |= !cont ? contains(Vec3(x - s, y - s, z + s)) : cont;
	cont |= !cont ? contains(Vec3(x - s, y + s, z - s)) : cont;
	cont |= !cont ? contains(Vec3(x + s, y - s, z - s)) : cont;
	cont |= !cont ? contains(Vec3(x - s, y + s, z + s)) : cont;
	cont |= !cont ? contains(Vec3(x + s, y - s, z + s)) : cont;
	cont |= !cont ? contains(Vec3(x + s, y + s, z - s)) : cont;
	cont |= !cont ? contains(Vec3(x + s, y + s, z + s)) : cont;

	// returns if it was contained
	return cont;
}

bool Frustum::contains(const Vec3& pt) const
{
	// if the point is above all the planes then it lies inside
	bool fail = false;
	GEfloat distA, distB, distC;
	Vec3 u;
	Vec3 v;
	for (GEint p = 0; !fail && p < 6; p += 2)
	{
		// calculates distance to two planes
		distA = mBounds[p].dist(pt);
		distB = mBounds[p + 1].dist(pt);

		// calculates vectors that connect closest point to cube point
		u = mBounds[p].normal() * distA + pt;
		v = mBounds[p + 1].normal() * distB + pt;

		// calculates the distance between those two points
		distC = glm::distance(u, v);

		// if distance C is not greater than both of the others then
		// the point lies outside of the bounds
		// this is based on the logic that the shortest distances between the point
		// and planes should be less than the distance between those two planes through
		// that point
		fail = distC < distA || distC < distB;
	}

	return !fail;
}