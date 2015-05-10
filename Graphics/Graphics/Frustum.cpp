#include "Frustum.h"
#define NTL 0
#define NTR 1
#define NBL 2
#define NBR 3
#define FTL 4
#define FTR 5
#define FBL 6
#define FBR 7

using namespace graphics;

Frustum::Frustum()
{
}

Frustum::Frustum(Vec3* verts)
{
	// NTL, NTR, NBL, NBR, FTL, FTR, FBL, FBR 
	// L, R, T, B, F, N
	// all constructed CCW
	
	// prefers far points since they are scaled more and less likely to cause rounding errors
	// left
	mBounds[0] = Plane(verts[NBL], verts[FBL], verts[FTL]);
	// right
	mBounds[1] = Plane(verts[NTR], verts[FTR], verts[FBR]);
	// top
	mBounds[2] = Plane(verts[NTL], verts[FTL], verts[FTR]);
	// bottom
	mBounds[3] = Plane(verts[NBR], verts[FBR], verts[FBL]);
	// far
	mBounds[4] = Plane(verts[FTR], verts[FTL], verts[FBL]);
	// near
	mBounds[5] = Plane(verts[NTL], verts[NTR], verts[NBR]);

	printf("Frustum Left Plane: normal: <%f %f %f> d: %f\n", mBounds[0].normal().x, mBounds[0].normal().y, mBounds[0].normal().z, mBounds[0].d());
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
	GEfloat s = cube.w;

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
		u = pt + mBounds[p].normal() * distA;
		v = pt + mBounds[p + 1].normal() * distB;
		//printf("PT: <%f, %f, %f>    PlaneA: <%f, %f, %f>    PlaneB: <%f, %f, %f>\n", pt.x, pt.y, pt.z, u.x, u.y, u.z, v.x, v.y, v.z);

		// gets absolute values of distances
		distA = fabsf(distA);
		distB = fabsf(distB);

		// calculates the distance between those two points
		distC = fabsf(glm::distance(u, v));

		// if distance C is not greater than both of the others then
		// the point lies outside of the bounds
		// this is based on the logic that the shortest distances between the point
		// and planes should be less than the distance between those two planes through
		// that point
		fail = distC < distA || distC < distB;
	}

	return !fail;
}