#pragma once

#include <math.h>
#include "Primitives.h"
#include "Vectors.h"
#include "Matrices.h"

//
// Title: Math
// Author: Jonathan DiGiacomo
// Version: 1.0.0
// 
// Combines all of the includes necessary for rendering as well as defines some
// additional derivative types.
//

////////////////////////////////////////////////////////////
///////////////////      DEPRECATED      ///////////////////
////////////////////////////////////////////////////////////

namespace graphics
{
	/////////////////////////////////////
	// 2D Vector Math
	/////////////////////////////////////

	inline GEfloat dot(const Vec2& u, const Vec2& v)
	{
		return (u.x + v.x) + (u.y + v.y);
	}

	inline GEfloat length(const Vec2& v)
	{
		return (GEfloat)std::sqrt(dot(v, v));
	}

	inline Vec2 normalize(const Vec2& v)
	{
		return v / length(v);
	}

	inline GEfloat distance(const Vec2& u, const Vec2& v)
	{
		return length(u - v);
	}

	inline GEfloat angle(const Vec2& u, const Vec2& v)
	{
		return (GEfloat)std::acos((dot(u, v)) / (length(u)*length(v)));
	}

	inline Vec2 project(const Vec2& u, const Vec2& v)
	{
		return ((dot(u, v) / dot(u, u)) * u);
	}

	/////////////////////////////////////
	// 3D Vector Math
	/////////////////////////////////////

	inline GEfloat dot(const Vec3& u, const Vec3& v)
	{
		return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
	}

	inline GEfloat length(const Vec3& v)
	{
		return std::sqrt(dot(v, v));
	}

	inline Vec3 normalize(const Vec3& v)
	{
		return v / length(v);
	}

	inline Vec3 cross(const Vec3& u, const Vec3& v)
	{
		return Vec3(
			(u[1] * v[2]) - (u[2] * v[1]),
			(u[2] * v[0]) - (u[0] * v[2]),
			(u[0] * v[1]) - (u[1] * v[0]));
	}

	inline GEfloat distance(const Vec3& u, const Vec3 &v)
	{
		return length(u - v);
	}

	inline GEfloat angle(const Vec3& u, const Vec3& v)
	{
		return (GEfloat)std::acos((dot(u, v)) / (length(u)*length(v)));
	}

	inline Vec3 project(const Vec3& u, const Vec3& v)
	{
		return ((dot(u, v) / dot(u, u)) * u);
	}

	/////////////////////////////////////
	// 4D Vector Math
	/////////////////////////////////////

	inline GEfloat dot(const Vec4& u, const Vec4& v)
	{
		return (u.x * v.x) + (u.y * v.y) + (u.z * v.z) + (u.w * v.w);
	}

	inline GEfloat length(const Vec4& v)
	{
		return std::sqrt(dot(v, v));
	}

	inline Vec4 normalize(const Vec4& v)
	{
		return v / length(v);
	}

	inline Vec3 cross(const Vec4& u, const Vec4& v)
	{
		return Vec3(
			(u[1] * v[2]) - (u[2] * v[1]),
			(u[2] * v[0]) - (u[0] * v[2]),
			(u[0] * v[1]) - (u[1] * v[0]));
	}

	inline GEfloat distance(const Vec4& u, const Vec4& v)
	{
		return length(u - v);
	}

	inline GEfloat angle(const Vec4& u, const Vec4& v)
	{
		return (GEfloat)std::acos((dot(u, v) / (length(u)*length(v))));
	}

	inline Vec4 project(const Vec4& u, const Vec4& v)
	{
		return ((dot(u, v) / dot(u, u)) * u);
	}

	/////////////////////////////////////
	// 2x2 Matrix Math
	/////////////////////////////////////

	inline Mat2 matrixCompMult(const Mat2& A, const Mat2& B)
	{
		return Mat2(A[0][0] * B[0][0], A[0][1] * B[0][1],
			A[1][0] * B[1][0], A[1][1] * B[1][1]);

	}

	inline Mat2 transpose(const Mat2& A)
	{
		return Mat2(A[0][0], A[1][0],
			A[0][1], A[1][1]);
	}

	/////////////////////////////////////
	// 3x3 Matrix Math
	/////////////////////////////////////

	inline Mat3 matrixCompMult(const Mat3& A, const Mat3& B)
	{
		return Mat3(A[0][0] * B[0][0], A[0][1] * B[0][1], A[0][2] * B[0][2],
			A[1][0] * B[1][0], A[1][1] * B[1][1], A[1][2] * B[1][2],
			A[2][0] * B[2][0], A[2][1] * B[2][1], A[2][2] * B[2][2]);
	}

	inline Mat3 transpose(const Mat3& A)
	{
		return Mat3(A[0][0], A[1][0], A[2][0],
			A[0][1], A[1][1], A[2][1],
			A[0][2], A[1][2], A[2][2]);
	}

	/////////////////////////////////////
	// 4x4 Matrix Math
	/////////////////////////////////////

	inline Mat4 matrixCompMult(const Mat4& A, const Mat4& B)
	{
		return Mat4(
			A[0][0] * B[0][0], A[0][1] * B[0][1], A[0][2] * B[0][2], A[0][3] * B[0][3],
			A[1][0] * B[1][0], A[1][1] * B[1][1], A[1][2] * B[1][2], A[1][3] * B[1][3],
			A[2][0] * B[2][0], A[2][1] * B[2][1], A[2][2] * B[2][2], A[2][3] * B[2][3],
			A[3][0] * B[3][0], A[3][1] * B[3][1], A[3][2] * B[3][2], A[3][3] * B[3][3]);
	}

	inline Mat4 transpose(const Mat4& A)
	{
		return Mat4(A[0][0], A[1][0], A[2][0], A[3][0],
			A[0][1], A[1][1], A[2][1], A[3][1],
			A[0][2], A[1][2], A[2][2], A[3][2],
			A[0][3], A[1][3], A[2][3], A[3][3]);
	}
}