#pragma once

#include "Vectors.h"

//
// Title: Matrices
// Author: Jonathan DiGiacomo
// Version: 1.0.0
//
// Provides basic matrice functionality.
//
// Heavilty based on code by Edward Angel in Interactive Computer Graphics, 6th ed.
//

////////////////////////////////////////////////////////////
///////////////////      DEPRECATED      ///////////////////
////////////////////////////////////////////////////////////

namespace graphics {
	/////////////////////////////////////
	// 2d matrix
	/////////////////////////////////////
	class Mat2 {
	private:
		Vec2 _m[2];
	public:
		//
		// constructors
		//
		Mat2(const GEfloat d = GEfloat(1.0));
		// vertical layout
		Mat2(const Vec2& i, const Vec2& j);
		// horizontal layout
		Mat2(GEfloat m00, GEfloat m01, GEfloat m10, GEfloat m11);
		Mat2(const Mat2& m);
		//
		// Indexing
		//
		Vec2& operator [] (int i);
		const Vec2& operator[] (int i) const;
		// Arithmetic (Non-Modifying)
		Mat2 operator + (const Mat2& m) const;
		Mat2 operator - (const Mat2& m) const;
		Mat2 operator * (const GEfloat s) const;
		Mat2 operator / (const GEfloat s) const;
		friend Mat2 operator * (const GEfloat s, const Mat2& m) { return m * s; }
		Mat2 operator * (const Mat2& m) const;
		Mat2 operator >> (const Mat2& m) const; // return result of prepending a matrix to this
		Mat2 operator << (const Mat2& m) const; // return result of appending a matrix to this
		//
		// Arithmetic (Modifying)
		//
		Mat2& operator += (const Mat2& m);
		Mat2& operator -= (const Mat2& m);
		Mat2& operator *= (const GEfloat s);
		Mat2& operator *= (const Mat2& m);
		Mat2& operator /= (const GEfloat s);
		Mat2& operator >>= (const Mat2& m); // use to prepend a matrix to this
		Mat2& operator <<= (const Mat2& m); // use to append a matrix to this
		//
		// Matrix/Vector Operators
		//
		Vec2 operator * (const Vec2& v) const;
		//
		// Conversion Operators
		//
		operator const GEfloat* () const;
		operator GEfloat* ();
	};

	/////////////////////////////////////
	// 3d matrix
	/////////////////////////////////////
	class Mat3
	{
	private:
		Vec3 _m[3];
	public:
		//
		// Constructors
		//
		Mat3(const GEfloat d = GEfloat(1.0));
		// vertical layout
		Mat3(const Vec3& i, const Vec3& j, const Vec3& k);
		// horizontal layout
		Mat3(GEfloat m00, GEfloat m01, GEfloat m02,
			 GEfloat m10, GEfloat m11, GEfloat m12,
			 GEfloat m20, GEfloat m21, GEfloat m22);
		Mat3(const Mat3& m);
		//
		// Indexing
		//
		Vec3& operator [] (int i);
		const Vec3& operator [] (int i) const;
		//
		// Arithmetic (Non-Modifying)
		//
		Mat3 operator + (const Mat3& m) const;
		Mat3 operator - (const Mat3& m) const;
		Mat3 operator * (const GEfloat s) const;
		Mat3 operator / (const GEfloat s) const;
		friend Mat3 operator * (const GEfloat s, const Mat3& m) { return s * m; }
		Mat3 operator * (const Mat3& m) const;
		Mat3 operator >> (const Mat3& m) const; // return result of prepending a matrix to this
		Mat3 operator << (const Mat3& m) const; // return result of appending a matrix to this
		//
		// Arithmetic (Modifying)
		//
		Mat3& operator += (const Mat3& m);
		Mat3& operator -= (const Mat3& m);
		Mat3& operator *= (const GEfloat s);
		Mat3& operator *= (const Mat3& m);
		Mat3& operator /= (const GEfloat s);
		Mat3& operator >>= (const Mat3& m); // use to prepend a matrix to this
		Mat3& operator <<= (const Mat3& m); // use to append a matrix to this
		//
		// Matrix/Vector Operators
		//
		Vec3 operator * (const Vec3& v) const;
		//
		// Conversion Operators
		//
		operator const GEfloat* () const;
		operator GEfloat* ();
	};

	/////////////////////////////////////
	// 4d matrix
	/////////////////////////////////////
	class Mat4
	{
	private:
		Vec4 _m[4];
	public:
		//
		// Constructor
		//
		Mat4(const GEfloat d = GEfloat(1.0));
		// vertical layout
		Mat4(const Vec4& i, const Vec4& j, const Vec4& k, const Vec4& l);
		// horizontal layout
		Mat4(GEfloat m00, GEfloat m01, GEfloat m02, GEfloat m03,
			 GEfloat m10, GEfloat m11, GEfloat m12, GEfloat m13,
			 GEfloat m20, GEfloat m21, GEfloat m22, GEfloat m23,
			 GEfloat m30, GEfloat m31, GEfloat m32, GEfloat m33);
		Mat4(const Mat4& m);
		//
		// Indexing
		//
		Vec4& operator [] (int i);
		const Vec4& operator [] (int i) const;
		//
		// Arithmetic (Non-Modifying)
		//
		Mat4 operator + (const Mat4& m) const;
		Mat4 operator - (const Mat4& m) const;
		Mat4 operator * (const GEfloat s) const;
		Mat4 operator / (const GEfloat s) const;
		friend Mat4 operator * (const GEfloat s, const Mat4& m) { return s * m; }
		Mat4 operator * (const Mat4& m) const;
		Mat4 operator >> (const Mat4& m) const; // return result of prepending a matrix to this
		Mat4 operator << (const Mat4& m) const; // return result of appending a matrix to this
		//
		// Arithmetic (Modifying)
		//
		Mat4& operator += (const Mat4& m);
		Mat4& operator -= (const Mat4& m);
		Mat4& operator *= (const GEfloat s);
		Mat4& operator *= (const Mat4& m);
		Mat4& operator /= (const GEfloat s);
		Mat4& operator >>= (const Mat4& m); // use to prepend a matrix to this
		Mat4& operator <<= (const Mat4& m); // use to append a matrix to this
		//
		// Matrix/Vector Operator
		//
		Vec4 operator * (const Vec4& v) const;
		//
		// Conversion Operators
		//
		operator const GEfloat* () const;
		operator GEfloat* ();
	};
}