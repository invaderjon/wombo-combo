#pragma once

#include <math.h>
#include "primitives.h"
#include "vec.h"
#include "mat.h"

//
// Title: Math
// Author: Jonathan DiGiacomo
// Version: 1.0.0
// 
// Combines all of the includes necessary for rendering as well as defines some
// additional derivative types.
//

namespace graphics
{
	/////////////////////////////////////
	// 2D Vector Math
	/////////////////////////////////////

	inline GEfloat dot(const vec2& u, const vec2& v)
	{
		return (u.x + v.x) + (u.y + v.y);
	}

	inline GEfloat length(const vec2& v)
	{
		return (GEfloat)std::sqrt(dot(v, v));
	}

	inline vec2 normalize(const vec2& v)
	{
		return v / length(v);
	}

	inline GEfloat distance(const vec2& u, const vec2& v)
	{
		return length(u - v);
	}

	inline GEfloat angle(const vec2& u, const vec2& v)
	{
		return (GEfloat)std::acos((dot(u, v)) / (length(u)*length(v)));
	}

	inline vec2 project(const vec2& u, const vec2& v)
	{
		return ((dot(u, v) / dot(u, u)) * u);
	}

	/////////////////////////////////////
	// 3D Vector Math
	/////////////////////////////////////

	inline GEfloat dot(const vec3& u, const vec3& v)
	{
		return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
	}

	inline GEfloat length(const vec3& v)
	{
		return std::sqrt(dot(v, v));
	}

	inline vec3 normalize(const vec3& v)
	{
		return v / length(v);
	}

	inline vec3 cross(const vec3& u, const vec3& v)
	{
		return vec3(
			(u[1] * v[2]) - (u[2] * v[1]),
			(u[2] * v[0]) - (u[0] * v[2]),
			(u[0] * v[1]) - (u[1] * v[0]));
	}

	inline GEfloat distance(const vec3& u, const vec3 &v)
	{
		return length(u - v);
	}

	inline GEfloat angle(const vec3& u, const vec3& v)
	{
		return (GEfloat)std::acos((dot(u, v)) / (length(u)*length(v)));
	}

	inline vec3 project(const vec3& u, const vec3& v)
	{
		return ((dot(u, v) / dot(u, u)) * u);
	}

	/////////////////////////////////////
	// 4D Vector Math
	/////////////////////////////////////

	inline GEfloat dot(const vec4& u, const vec4& v)
	{
		return (u.x * v.x) + (u.y * v.y) + (u.z * v.z) + (u.w * v.w);
	}

	inline GEfloat length(const vec4& v)
	{
		return std::sqrt(dot(v, v));
	}

	inline vec4 normalize(const vec4& v)
	{
		return v / length(v);
	}

	inline vec3 cross(const vec4& u, const vec4& v)
	{
		return vec3(
			(u[1] * v[2]) - (u[2] * v[1]),
			(u[2] * v[0]) - (u[0] * v[2]),
			(u[0] * v[1]) - (u[1] * v[0]));
	}

	inline GEfloat distance(const vec4& u, const vec4& v)
	{
		return length(u - v);
	}

	inline GEfloat angle(const vec4& u, const vec4& v)
	{
		return (GEfloat)std::acos((dot(u, v) / (length(u)*length(v))));
	}

	inline vec4 project(const vec4& u, const vec4& v)
	{
		return ((dot(u, v) / dot(u, u)) * u);
	}

	/////////////////////////////////////
	// 2x2 Matrix Math
	/////////////////////////////////////

	inline mat2 matrixCompMult(const mat2& A, const mat2& B)
	{
		return mat2(A[0][0] * B[0][0], A[0][1] * B[0][1],
			A[1][0] * B[1][0], A[1][1] * B[1][1]);

	}

	inline mat2 transpose(const mat2& A)
	{
		return mat2(A[0][0], A[1][0],
			A[0][1], A[1][1]);
	}

	/////////////////////////////////////
	// 3x3 Matrix Math
	/////////////////////////////////////

	inline mat3 matrixCompMult(const mat3& A, const mat3& B)
	{
		return mat3(A[0][0] * B[0][0], A[0][1] * B[0][1], A[0][2] * B[0][2],
			A[1][0] * B[1][0], A[1][1] * B[1][1], A[1][2] * B[1][2],
			A[2][0] * B[2][0], A[2][1] * B[2][1], A[2][2] * B[2][2]);
	}

	inline mat3 transpose(const mat3& A)
	{
		return mat3(A[0][0], A[1][0], A[2][0],
			A[0][1], A[1][1], A[2][1],
			A[0][2], A[1][2], A[2][2]);
	}

	/////////////////////////////////////
	// 4x4 Matrix Math
	/////////////////////////////////////

	inline mat4 matrixCompMult(const mat4& A, const mat4& B)
	{
		return mat4(
			A[0][0] * B[0][0], A[0][1] * B[0][1], A[0][2] * B[0][2], A[0][3] * B[0][3],
			A[1][0] * B[1][0], A[1][1] * B[1][1], A[1][2] * B[1][2], A[1][3] * B[1][3],
			A[2][0] * B[2][0], A[2][1] * B[2][1], A[2][2] * B[2][2], A[2][3] * B[2][3],
			A[3][0] * B[3][0], A[3][1] * B[3][1], A[3][2] * B[3][2], A[3][3] * B[3][3]);
	}

	inline mat4 transpose(const mat4& A)
	{
		return mat4(A[0][0], A[1][0], A[2][0], A[3][0],
			A[0][1], A[1][1], A[2][1], A[3][1],
			A[0][2], A[1][2], A[2][2], A[3][2],
			A[0][3], A[1][3], A[2][3], A[3][3]);
	}
}