#pragma once

#include "primitives.h"
#include "constants.h"
#include "vec.h"
#include "mat.h"
#include "math.h"

//
// Title: Graphics
// Author: Jonathan DiGiacomo
// Version: 1.0.0
// 
// Includes all essential rendering data types and methods.
//

namespace graphics
{

	/////////////////////////////////////
	// Vector Derivative Types
	/////////////////////////////////////
	// colors
	typedef struct vector3D color3; // rgb
	typedef struct vector4D color4; // rgba

	// vertices
	typedef struct vector2D vert2; // 2D vertex
	typedef struct vector3D vert3; // 3D vertex
	typedef struct vector4D vert4; // 4D vertex
}