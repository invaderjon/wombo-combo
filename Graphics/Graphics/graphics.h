#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
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
	typedef glm::vec2 Vec2;
	typedef glm::vec3 Vec3;
	typedef glm::vec4 Vec4;

	// matrices
	typedef glm::mat2x2 Mat2;
	typedef glm::mat3x3 Mat3;
	typedef glm::mat4x4 Mat4;

	// colors
	typedef struct vector3D Color3; // rgb
	typedef struct vector4D Color4; // rgba

	// vertices
	typedef Vec2 Vert2; // 2D vertex
	typedef Vec3 Vert3; // 3D vertex
	typedef Vec4 Vert4; // 4D vertex

	// normals
	typedef Vec2 Norm2; // 2D normal
	typedef Vec3 Norm3; // 3D normal
	typedef Vec4 Norm4; // 4D normal
}