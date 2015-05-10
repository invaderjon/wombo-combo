#pragma once

#include "Graphics.h"

namespace graphics
{
	struct Plane
	{
	private:
		Vec3	mNormal;
		GEfloat mConstant;
	public:
		Plane();
		Plane(const Vec3& normal, GEfloat d);
		Plane(const Vec3& a, const Vec3& b, const Vec3& c);
		~Plane();

		const Vec3& normal() const;
		GEfloat d() const;

		// calculates the distance to the plane
		GEfloat dist(const Vec3& point) const;
	};
};

