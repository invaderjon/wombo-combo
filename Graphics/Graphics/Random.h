#pragma once

#include <ctime>
#include <random>
#include <bitset>

#include "Primitives.h"

namespace graphics
{
	class Random
	{
		// generates random bits
		inline void random(GEbyte&  bits);
		inline void random(GEshort& bits);
		inline void random(GEint&   bits);
		inline void random(GElong&  bits);
		inline void random(GEubyte&  bits);
		inline void random(GEushort& bits);
		inline void random(GEuint&   bits);
		inline void random(GEulong&  bits);


		const GEint cRandSize = std::bitset<32>(RAND_MAX).count();

	public:
		Random();
		Random(GEuint seed);
		~Random();

		// integer types
		//GEbyte  next(GEbyte  minimum, GEbyte  maximum);
		//GEshort next(GEshort minimum, GEshort maximum);
		GEint   next(GEint   minimum, GEint   maximum);
		//GElong  next(GElong  minimum, GElong  maximum);

		// unsigned integer types
		//GEubyte  next(GEubyte  minimum, GEubyte  maximum);
		//GEushort next(GEushort minimum, GEushort maximum);
		//GEuint   next(GEuint   minimum, GEuint   maximum);
		//GEulong  next(GEulong  minimum, GEulong  maximum);

		// character
		//GEchar   next(GEchar minimum, GEchar maximum);

		// floating point
		GEfloat  next(GEfloat minimum, GEfloat maximum);
		//GEdouble next(GEdouble minimum, GEdouble maximum);
	};
}

