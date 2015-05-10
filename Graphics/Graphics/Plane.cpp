#include "Plane.h"

using namespace graphics;

Plane::Plane()
	: mNormal(0, 0, 1), mConstant(0)
{

}

Plane::Plane(const Vec3& normal, GEfloat d)
	: mNormal(normal), mConstant(d)
{

}

Plane::Plane(const Vec3& a, const Vec3& b, const Vec3& c)
{
	// Determines u & v vectors on plane P
	Vec3 u = b - a;
	Vec3 v = c - a;

	// Calculates the normal
	Vec3 n = glm::normalize(glm::cross(u, v));
	
	// Calculates d in ax + by + cz + d = 0 where <x, y, z> is point A
	GEfloat d = -glm::dot(a, n);

	// stores in local variables
	mNormal = n;
	mConstant = d;
}


Plane::~Plane()
{
}

const Vec3& Plane::normal() const
{
	return mNormal;
}

GEfloat Plane::d() const
{
	return mConstant;
}

GEfloat Plane::dist(const Vec3& pt) const
{
	// calculate plane's closest point to the origin
	Vec3 offset = -mConstant * mNormal;
	
	// offset system to origin
	Vec3 p = pt - offset;

	// project p onto normal
	return dot(p, mNormal);
}
