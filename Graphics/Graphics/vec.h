#pragma once

#include <iostream>
#include "primitives.h"

//
// Title: Vectors
// Author: Jonathan DiGiacomo
// Version: 1.0.0
//
// Provides basic vector functionality.
// 
// Heavilty based on code by Edward Angel in Interactive Computer Graphics, 6th ed.
//

namespace graphics
{
	/////////////////////////////////////
	// 2d Vector
	/////////////////////////////////////
	typedef struct vector2D {
		GEfloat x;
		GEfloat y;

		// Constructors
		vector2D(GEfloat s = GEfloat(0.0f)) :
			x(s), y(s) { }

		vector2D(GEfloat x, GEfloat y) :
			x(x), y(y) { }

		vector2D(const vector2D &v)
		{
			x = v.x;
			y = v.y;
		}

		// Operator overloads
		//
		// Indexing
		//
		GEfloat &operator [] (int i) {
			return *(&x + i);
		}
		const GEfloat operator [] (int i) const {
			return *(&x + i);
		}

		//
		// Arithmetic Operators (non-modifying)
		//
		vector2D operator - () const // unary minus operator
		{
			return vector2D(-x, -y);
		}
		vector2D operator + (const vector2D &v) const
		{
			return vector2D(x + v.x, y + v.y);
		}
		vector2D operator - (const vector2D &v) const
		{
			return vector2D(x - v.x, y - v.y);
		}
		vector2D operator * (const GEfloat s) const
		{
			return vector2D(s * x, s * y);
		}
		vector2D operator * (const vector2D &v) const
		{
			return vector2D(x * v.x, y * v.y);
		}
		friend vector2D operator * (const GEfloat s, const vector2D &v)
		{
			return v * s;
		}
		vector2D operator / (const GEfloat s) const {
#ifdef DEBUG
			if (std::fabs(s) < DivideByZeroTolerance) {
				std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
					<< "Division by zero" << std::endl;
				return vector2D();
			}
#endif // DEBUG
			GEfloat r = GEfloat(1.0) / s;
			return *this * r;
		}

		//
		// Arithmetic Operators (modifying)
		//
		vector2D &operator += (const vector2D &v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}
		vector2D &operator -= (const vector2D &v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}
		vector2D &operator *= (const GEfloat s)
		{
			x *= s;
			y *= s;
			return *this;
		}
		vector2D &operator *= (const vector2D &v)
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}
		vector2D &operator /= (const GEfloat s)
		{
#ifdef DEBUG
			if (std::fabs(s) < DivideByZeroTolerance) {
				std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
					<< "Division by zero" << std::endl;
			}
#endif // DEBUG
			GEfloat r = GEfloat(1.0) / s;
			return *this *= r;
		}

		//
		// Insertion and Extraction Operators
		//
		friend std::ostream& operator << (std::ostream &os, const vector2D &v)
		{
			return os << "( " << v.x << ", " << v.y << " )";
		}
		friend std::istream &operator >> (std::istream &is, vector2D &v)
		{
			return is >> v.x >> v.y;
		}

		//
		// Conversion Operators
		//
		operator const GEfloat* () const
		{
			return static_cast<const GEfloat*>(&x);
		}
		operator GEfloat* ()
		{
			return static_cast<GEfloat*>(&x);
		}
	} vec2;

	/////////////////////////////////////
	// 3D Vector
	/////////////////////////////////////
	typedef struct vector3D {
		GEfloat x;
		GEfloat y;
		GEfloat z;

		//
		// Constructors
		//
		vector3D(GEfloat s = GEfloat(0.0f)) :
			x(s), y(s), z(s) {}

		vector3D(GEfloat x, GEfloat y, GEfloat z) :
			x(x), y(y), z(z) {}

		vector3D(const vector3D &v) {
			x = v.x;
			y = v.y;
			z = v.z;
		}

		vector3D(const vector2D &v)
		{
			x = v.x;
			y = v.y;
			z = GEfloat(0.0f);
		}

		vector3D(const vector2D &v, const GEfloat f)
		{
			x = v.x;
			y = v.y;
			z = f;
		}


		// Operator overloads
		//
		// Indexing
		//
		GEfloat &operator [] (int i) {
			return *(&x + i);
		}
		const GEfloat operator [] (int i) const {
			return *(&x + i);
		}

		//
		// Arithmetic Operators (non-modifying)
		//
		vector3D operator - () const
		{
			return vector3D(-x, -y, -z);
		}
		vector3D operator + (const vector3D &v) const
		{
			return vector3D(x + v.x, y + v.y, z + v.z);
		}
		vector3D operator - (const vector3D &v) const
		{
			return vector3D(x - v.x, y - v.y, z - v.z);
		}
		vector3D operator * (const GEfloat s) const
		{
			return vector3D(x * s, y * s, z * s);
		}
		vector3D operator * (const vector3D &v) const
		{
			return vector3D(x * v.x, y * v.y, z * v.z);
		}
		friend vector3D operator * (const GEfloat s, const vector3D &v)
		{
			return v * s;
		}
		vector3D operator / (const GEfloat s) const
		{
#ifdef DEBUG
			if (std::fabs(s) < DivideByZeroTolerance) {
				std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
					<< "Division by zero" << std::endl;
				return vec3();
			}
#endif // DEBUG
			GEfloat r = GEfloat(1.0) / s;
			return *this * r;
		}

		//
		// Arithmetic Operators (modifying)
		//
		vector3D &operator += (const vector3D &v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		vector3D &operator -= (const vector3D &v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		vector3D &operator *= (const GEfloat s)
		{
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}
		vector3D &operator /= (const GEfloat s)
		{
#ifdef DEBUG
			if (std::fabs(s) < DivideByZeroTolerance) {
				std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
					<< "Division by zero" << std::endl;
			}
#endif // DEBUG
			GEfloat r = GEfloat(1.0) / s;
			return *this *= r;
		}

		//
		// Insertion and Extraction Operators
		//
		friend std::ostream& operator << (std::ostream& os, const vector3D& v)
		{
			return os << "( " << v.x << ", " << v.y << ", " << v.z << " )";
		}

		friend std::istream& operator >> (std::istream& is, vector3D& v)
		{
			return is >> v.x >> v.y >> v.z;
		}
	} vec3;

	/////////////////////////////////////
	// 4D Vector
	/////////////////////////////////////
	typedef struct vector4D {
		GEfloat x;
		GEfloat y;
		GEfloat z;
		GEfloat w;

		//
		// Constructors
		//
		vector4D(GEfloat s = GEfloat(0.0f)) :
			x(s), y(s), z(s), w(s) {}

		vector4D(GEfloat x, GEfloat y, GEfloat z, GEfloat w) :
			x(x), y(y), z(z), w(w) {}

		vector4D(const vector4D &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
		}
		vector4D(const vector3D &v, const GEfloat s = GEfloat(1.0f))
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = s;
		}
		vector4D(const vector2D &v, const GEfloat s = GEfloat(1.0f))
		{
			x = v.x;
			y = v.y;
			z = s;
			w = s;
		}
		vector4D(const vector2D &v, GEfloat z, GEfloat w) :
			z(z), w(w)
		{
			x = v.x;
			y = v.y;
		}

		// Operator overloads
		//
		// Indexing
		//
		GEfloat &operator [] (int i) {
			return *(&x + i);
		}
		const GEfloat operator [] (int i) const {
			return *(&x + i);
		}

		//
		// Arithmetic Operators (non-modifying)
		//
		vector4D operator - () const
		{
			return vector4D(-x, -y, -z, -w);
		}
		vector4D operator + (const vector4D &v) const
		{
			return vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
		}
		vector4D operator - (const vector4D &v) const
		{
			return vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
		}
		vector4D operator * (const GEfloat s) const
		{
			return vector4D(x * s, y * s, z * s, w * s);
		}
		vector4D operator * (const vector4D &v) const
		{
			return vector4D(x * v.x, y * v.y, z * v.z, w * v.w);
		}
		friend vector4D operator * (const GEfloat s, const vector4D &v)
		{
			return v * s;
		}
		vector4D operator / (const GEfloat s) const
		{
#ifdef DEBUG
			if (std::fabs(s) < DivideByZeroTolerance) {
				std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
					<< "Division by zero" << std::endl;
				return vec4();
			}
#endif // DEBUG
			GEfloat r = GEfloat(1.0) / s;
			return *this * r;
		}

		//
		// Arithmetic Operators (modifying)
		//
		vector4D &operator += (const vector4D &v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
			return *this;
		}
		vector4D operator -= (const vector4D &v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return *this;
		}
		vector4D &operator *= (const GEfloat s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}
		vector4D &operator *= (const vector4D &v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			w *= v.w;
			return *this;
		}
		vector4D &operator /= (const GEfloat s)
		{
#ifdef DEBUG
			if (std::fabs(s) < DivideByZeroTolerance) {
				std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
					<< "Division by zero" << std::endl;
			}
#endif // DEBUG
			GEfloat r = GEfloat(1.0) / s;
			return *this *= r;
		}

		//
		// Insertion and Extraction Operators
		//
		friend std::ostream& operator << (std::ostream& os, const vector4D& v)
		{
			return os << "( " << v.x << ", " << v.y
				<< ", " << v.z << ", " << v.w << " )";
		}
		friend std::istream& operator >> (std::istream& is, vector4D& v)
		{
			return is >> v.x >> v.y >> v.z >> v.w;
		}

		//
		// Conversion Operators
		//
		operator const GEfloat* () const
		{
			return static_cast<const GEfloat*>(&x);
		}
		operator GEfloat* ()
		{
			return static_cast<GEfloat*>(&x);
		}
	} vec4;
}