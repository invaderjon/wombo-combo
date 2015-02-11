#pragma once

#include "vec.h"

//
// Title: Matrices
// Author: Jonathan DiGiacomo
// Version: 1.0.0
//
// Provides basic matrice functionality.
//
// Heavilty based on code by Edward Angel in Interactive Computer Graphics, 6th ed.
//

namespace graphics {
	/////////////////////////////////////
	// 2d matrix
	/////////////////////////////////////
	class mat2 {
	private:
		vec2 _m[2];
	public:
		//
		// constructors
		//
		mat2(const GEfloat d = GEfloat(1.0));
		// vertical layout
		mat2(const vec2& i, const vec2& j);
		// horizontal layout
		mat2(GEfloat m00, GEfloat m01, GEfloat m10, GEfloat m11);
		mat2(const mat2& m);
		//
		// Indexing
		//
		vec2& operator [] (int i);
		const vec2& operator[] (int i) const;
		// Arithmetic (Non-Modifying)
		mat2 operator + (const mat2& m) const;
		mat2 operator - (const mat2& m) const;
		mat2 operator * (const GEfloat s) const;
		mat2 operator / (const GEfloat s) const;
		friend mat2 operator * (const GEfloat s, const mat2& m) { return m * s; }
		mat2 operator * (const mat2& m) const;
		mat2 operator >> (const mat2& m) const; // return result of prepending a matrix to this
		mat2 operator << (const mat2& m) const; // return result of appending a matrix to this
		//
		// Arithmetic (Modifying)
		//
		mat2& operator += (const mat2& m);
		mat2& operator -= (const mat2& m);
		mat2& operator *= (const GEfloat s);
		mat2& operator *= (const mat2& m);
		mat2& operator /= (const GEfloat s);
		mat2& operator >>= (const mat2& m); // use to prepend a matrix to this
		mat2& operator <<= (const mat2& m); // use to append a matrix to this
		//
		// Matrix/Vector Operators
		//
		vec2 operator * (const vec2& v) const;
		//
		// Conversion Operators
		//
		operator const GEfloat* () const;
		operator GEfloat* ();
	};

	/////////////////////////////////////
	// 3d matrix
	/////////////////////////////////////
	class mat3
	{
	private:
		vec3 _m[3];
	public:
		//
		// Constructors
		//
		mat3(const GEfloat d = GEfloat(1.0));
		// vertical layout
		mat3(const vec3& i, const vec3& j, const vec3& k);
		// horizontal layout
		mat3(GEfloat m00, GEfloat m01, GEfloat m02,
			 GEfloat m10, GEfloat m11, GEfloat m12,
			 GEfloat m20, GEfloat m21, GEfloat m22);
		mat3(const mat3& m);
		//
		// Indexing
		//
		vec3& operator [] (int i);
		const vec3& operator [] (int i) const;
		//
		// Arithmetic (Non-Modifying)
		//
		mat3 operator + (const mat3& m) const;
		mat3 operator - (const mat3& m) const;
		mat3 operator * (const GEfloat s) const;
		mat3 operator / (const GEfloat s) const;
		friend mat3 operator * (const GEfloat s, const mat3& m) { return s * m; }
		mat3 operator * (const mat3& m) const;
		mat3 operator >> (const mat3& m) const; // return result of prepending a matrix to this
		mat3 operator << (const mat3& m) const; // return result of appending a matrix to this
		//
		// Arithmetic (Modifying)
		//
		mat3& operator += (const mat3& m);
		mat3& operator -= (const mat3& m);
		mat3& operator *= (const GEfloat s);
		mat3& operator *= (const mat3& m);
		mat3& operator /= (const GEfloat s);
		mat3& operator >>= (const mat3& m); // use to prepend a matrix to this
		mat3& operator <<= (const mat3& m); // use to append a matrix to this
		//
		// Matrix/Vector Operators
		//
		vec3 operator * (const vec3& v) const;
		//
		// Conversion Operators
		//
		operator const GEfloat* () const;
		operator GEfloat* ();
	};

	/////////////////////////////////////
	// 4d matrix
	/////////////////////////////////////
	class mat4
	{
	private:
		vec4 _m[4];
	public:
		//
		// Constructor
		//
		mat4(const GEfloat d = GEfloat(1.0));
		// vertical layout
		mat4(const vec4& i, const vec4& j, const vec4& k, const vec4& l);
		// horizontal layout
		mat4(GEfloat m00, GEfloat m01, GEfloat m02, GEfloat m03,
			 GEfloat m10, GEfloat m11, GEfloat m12, GEfloat m13,
			 GEfloat m20, GEfloat m21, GEfloat m22, GEfloat m23,
			 GEfloat m30, GEfloat m31, GEfloat m32, GEfloat m33);
		mat4(const mat4& m);
		//
		// Indexing
		//
		vec4& operator [] (int i);
		const vec4& operator [] (int i) const;
		//
		// Arithmetic (Non-Modifying)
		//
		mat4 operator + (const mat4& m) const;
		mat4 operator - (const mat4& m) const;
		mat4 operator * (const GEfloat s) const;
		mat4 operator / (const GEfloat s) const;
		friend mat4 operator * (const GEfloat s, const mat4& m) { return s * m; }
		mat4 operator * (const mat4& m) const;
		mat4 operator >> (const mat4& m) const; // return result of prepending a matrix to this
		mat4 operator << (const mat4& m) const; // return result of appending a matrix to this
		//
		// Arithmetic (Modifying)
		//
		mat4& operator += (const mat4& m);
		mat4& operator -= (const mat4& m);
		mat4& operator *= (const GEfloat s);
		mat4& operator *= (const mat4& m);
		mat4& operator /= (const GEfloat s);
		mat4& operator >>= (const mat4& m); // use to prepend a matrix to this
		mat4& operator <<= (const mat4& m); // use to append a matrix to this
		//
		// Matrix/Vector Operator
		//
		vec4 operator * (const vec4& v) const;
		//
		// Conversion Operators
		//
		operator const GEfloat* () const;
		operator GEfloat* ();
	};
}