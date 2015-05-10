#pragma once

#include "Graphics.h"

namespace graphics
{
	// todo: modify to any precision
	class Sphere
	{
	private:
		Vec3 mCenter;
		GEfloat mRadius;

	public:
		Sphere();
		Sphere(const Vec3& center, GEfloat radius);
		~Sphere();

		GEfloat radius() const;
		void radius(GEfloat radius);

		const Vec3& center() const;
		void center(const Vec3& center);

		// Check if the volume contains a point
		bool contains(const Vec3& point);
	};

};