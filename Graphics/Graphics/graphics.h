#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Platform.h"
#include "Primitives.h"
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
	// vectors
	typedef glm::fvec2 Vec2;
	typedef glm::fvec3 Vec3;
	typedef glm::fvec4 Vec4;
	typedef glm::fquat Quat;

	// matrices
	typedef glm::fmat2x2 Mat2;
	typedef glm::fmat3x3 Mat3;
	typedef glm::fmat4x4 Mat4;

	// colors
	typedef Vec3 Color3; // rgb
	typedef Vec4 Color4; // rgba

	// vertices
	typedef Vec2 Vert2; // 2D vertex
	typedef Vec3 Vert3; // 3D vertex
	typedef Vec4 Vert4; // 4D vertex

	// normals
	typedef Vec2 Norm2; // 2D normal
	typedef Vec3 Norm3; // 3D normal
	typedef Vec4 Norm4; // 4D normal
}