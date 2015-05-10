#include "Sphere.h"

using namespace graphics;

Sphere::Sphere()
	: mCenter(0), mRadius(0)
{

}

Sphere::Sphere(const Vec3& center, GEfloat radius)
	: mCenter(center), mRadius(radius)
{

}

Sphere::~Sphere()
{
}

GEfloat Sphere::radius() const
{
	return mRadius;
}

void Sphere::radius(GEfloat radius)
{
	mRadius = radius;
}

const Vec3& Sphere::center() const
{
	return mCenter;
}

void Sphere::center(const Vec3& center)
{
	mCenter = center;
}

bool Sphere::contains(const Vec3& point)
{
	// Calculate distance from center
	GEfloat dist = glm::distance(mCenter, point);

	// if the distance is less then the radius then it's inside
	return dist <= mRadius;
}

