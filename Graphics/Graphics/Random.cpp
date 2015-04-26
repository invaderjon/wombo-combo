#include "Random.h"

using namespace graphics;

Random::Random()
{
	// sets seed
	srand(time(NULL));
}

Random::Random(GEuint seed)
{
	srand(seed);
}

Random::~Random()
{
}

// integer types
// byte
/*GEbyte Random::next(GEbyte minimum, GEbyte maximum)
{
	GEbyte d = maximum - minimum;
	GEbyte r;
	random(r);
	return minimum + r % d;
}
// short
GEshort Random::next(GEshort minimum, GEshort maximum)
{
	GEshort d = maximum - minimum;
	GEshort r;
	random(r);
	return minimum + r % d;
}*/
// int
GEint Random::next(GEint minimum, GEint maximum)
{
	GEint d = maximum - minimum;
	GEint r;
	random(r);
	return minimum + r % d;
}
// long
/*GElong Random::next(GElong minimum, GElong maximum)
{
	GElong d = maximum - minimum;
	GElong r;
	random(r);
	return minimum + (r % d);
}

// unsigned integer types
// unsigned byte
GEubyte Random::next(GEubyte minimum, GEubyte maximum)
{
	GEubyte d = maximum - minimum;
	GEbyte r;
	random(r);
	return minimum + r % d;
}
// unsigned short
GEushort Random::next(GEushort minimum, GEushort maximum)
{
	GEushort d = maximum - minimum;
	GEushort r;
	random(r);
	return minimum + r % d;
}
// unsigned int
GEuint Random::next(GEuint minimum, GEuint maximum)
{
	GEuint d = maximum - minimum;
	GEuint r;
	random(r);
	return minimum + r % d;
}
// unsigned long
GEulong Random::next(GEulong minimum, GEulong maximum)
{
	GEulong d = maximum - minimum;
	GEulong r;
	random(r);
	return minimum + (r % d);
}

// character
*/
// floating point
// float
GEfloat Random::next(GEfloat minimum, GEfloat maximum)
{
	GEuint r;
	random(r);
	GEuint m = 0xFFFFFFFF;
	GEfloat mult = static_cast <GEfloat> (r) / static_cast <GEfloat> (m);
	GEfloat diff = maximum - minimum;
	return mult*diff + minimum;
}
// double
/*GEdouble Random::next(GEdouble minimum, GEdouble maximum)
{
	GEulong r;
	random(r);
	GEulong m = 0xFFFFFFFFFFFFFFFF;
	GEdouble mult = static_cast<GEdouble> (r) / static_cast <GEdouble> (m);
	GEdouble diff = maximum - minimum;
	return mult*diff + minimum;
}*/

void Random::random(GEbyte& bits)
{
	bits = 0;
	for (GEint set = 0; set < sizeof(GEbyte); set += cRandSize)
		bits |= rand() << set;
}

void Random::random(GEshort& bits)
{
	bits = 0;
	for (GEint set = 0; set < sizeof(GEshort); set += cRandSize)
		bits |= rand() << set;
}

void Random::random(GEint& bits)
{
	bits = 0;
	for (GEint set = 0; set < sizeof(GEint); set += cRandSize)
		bits |= rand() << set;
}

void Random::random(GElong& bits)
{
	bits = 0;
	for (GEint set = 0; set << sizeof(GElong); set += cRandSize)
		bits |= rand() << set;
}

void Random::random(GEubyte& bits)
{
	bits = 0;
	for (GEuint set = 0; set < sizeof(GEubyte); set += cRandSize)
		bits |= rand() << set;
}

void Random::random(GEushort& bits)
{
	bits = 0;
	for (GEuint set = 0; set < sizeof(GEushort); set += cRandSize)
		bits |= rand() << set;
}

void Random::random(GEuint& bits)
{
	bits = 0;
	for (GEuint set = 0; set < sizeof(GEuint); set += cRandSize)
		bits |= rand() << set;
}

void Random::random(GEulong& bits)
{
	bits = 0;
	for (GEuint set = 0; set << sizeof(GEulong); set += cRandSize)
		bits |= rand() << set;
}