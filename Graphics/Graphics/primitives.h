#pragma once

#include "Platform.h"

//
// Title: Primitives
// Author: Jonathan DiGiacomo
// Version: 1.0.0
//
// Defines engine primitive data types.
//

namespace graphics
{
	// floating point
	typedef GLdouble GEdouble;
	typedef GLfloat GEfloat;

	// signed ints
	typedef GLint GEint;
	typedef GLshort GEshort;
	typedef GLbyte GEbyte;

	// unsigned ints
	typedef unsigned long long GEulong;
	typedef GLuint GEuint;
	typedef GLushort GEushort;
	typedef GLubyte GEubyte;

	// char
	typedef GLchar GEchar;

	// boolean
	typedef GLboolean GEboolean;

	// enum
	typedef GLenum GEenum;
}