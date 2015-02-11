#include "mat.h"

using namespace graphics;

//
//
// 2D Matrix
//
//

mat2::mat2(const GEfloat d)
{
	_m[0][0] = d;
	_m[1][1] = d;
}

mat2::mat2(const vec2& i, const vec2& j)
{
	_m[0] = i;
	_m[2] = j;
}

mat2::mat2(GEfloat m00, GEfloat m01,
		   GEfloat m10, GEfloat m11)
{
	_m[0] = vec2(m00, m10);
	_m[1] = vec2(m01, m11);
}

mat2::mat2(const mat2& m)
{
	if (*this != m)
	{
		_m[0] = m[0];
		_m[1] = m[1];
	}
}

vec2& mat2::operator[] (int i)
{
	return _m[i];
}

const vec2& mat2::operator [] (int i) const
{
	return _m[i];
}

mat2 mat2::operator + (const mat2& m) const
{
	return mat2(_m[0] + m[0], _m[1] + m[1]);
}

mat2 mat2::operator - (const mat2& m) const
{
	return mat2(_m[0] - m[0], _m[1] - m[1]);
}

mat2 mat2::operator * (const GEfloat s) const
{
	return mat2(s*_m[0], s*_m[1]);
}

mat2 mat2::operator / (const GEfloat s) const
{
#ifdef DEBUG
	if (std::fabs(s) < DivideByZeroTolerance) 
	{
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
			<< "Division by zero" << std::endl;
	}
#endif
	GEfloat r = GEfloat(1.0) / s;
	return *this * r;
}

mat2 mat2::operator * (const mat2& m) const
{
	mat2 a(0.0);
	int i;
	int j;
	int k;

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			for (k = 0; k < 2; k++)
				a[i][j] += _m[i][k] * m[k][j];
	return a;
}

mat2 mat2::operator >> (const mat2& m) const
{
	// applies m then applies this
	return *this * m;
}

mat2 mat2::operator << (const mat2& m) const
{
	// applies this then applies m
	return m * *this;
}

mat2& mat2::operator += (const mat2& m)
{
	_m[0] += m[0];
	_m[1] += m[1];
	return *this;
}

mat2& mat2::operator -= (const mat2& m)
{
	_m[0] -= m[0];
	_m[1] -= m[1];
	return *this;
}

mat2& mat2::operator *= (const GEfloat s)
{
	_m[0] *= s;
	_m[1] *= s;
	return *this;
}

mat2& mat2::operator *= (const mat2& m)
{
	mat2 a(0.0);
	int i;
	int j;
	int k;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			for (k = 0; k < 2; k++)
				a[i][j] += _m[i][k] * m[k][j];
	return *this = a;
}

mat2& mat2::operator /= (const GEfloat s)
{
#ifdef DEBUG
	if (std::fabs(s) < DivideByZeroTolerance) {
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
			<< "Division by zero" << std::endl;
		return mat2();
	}
#endif
	GEfloat r = GEfloat(1.0) / s;
	return *this *= r;
}

vec2 mat2::operator * (const vec2& v) const
{
	return vec2(_m[0][0] * v.x + _m[0][1] * v.y,
				_m[1][0] * v.x + _m[1][1] * v.y);
}

mat2& mat2::operator <<= (const mat2& m)
{
	return *this *= m;
}

mat2& mat2::operator >>= (const mat2& m)
{
	return (*this = (m * *this));
}

mat2::operator const GEfloat* () const
{
	return static_cast<const GEfloat*>(&_m[0].x);
}

mat2::operator GEfloat* ()
{
	return static_cast<GEfloat*>(&_m[0].x);
}


//
//
// 3D Matrix
//
//

mat3::mat3(const GEfloat d)
{
	_m[0][0] = d;
	_m[1][1] = d;
	_m[2][2] = d;
}

mat3::mat3(const vec3& i, const vec3& j, const vec3& k)
{
	_m[0] = i;
	_m[1] = j;
	_m[2] = k;
}

mat3::mat3(GEfloat m00, GEfloat m01, GEfloat m02,
		   GEfloat m10, GEfloat m11, GEfloat m12,
		   GEfloat m20, GEfloat m21, GEfloat m22)
{
	_m[0] = vec3(m00, m10, m20);
	_m[1] = vec3(m01, m11, m12);
	_m[2] = vec3(m02, m12, m22);
}

mat3::mat3(const mat3& m)
{
	if (*this != m)
	{
		_m[0] = m[0];
		_m[1] = m[1];
		_m[2] = m[2];
	}
}

vec3& mat3::operator [] (int i)
{
	return _m[i];
}

const vec3& mat3::operator [] (int i) const
{
	return _m[i];
}

mat3 mat3::operator + (const mat3& m) const
{
	return mat3(_m[0] + m[0], _m[1] + m[1], _m[2] + m[2]);
}

mat3 mat3::operator - (const mat3& m) const
{
	return mat3(_m[0] - m[0], _m[1] - m[1], _m[2] - m[2]);
}

mat3 mat3::operator * (const GEfloat s) const
{
	return mat3(s * _m[0], s * _m[1], s * _m[2]);
}

mat3 mat3::operator / (const GEfloat s) const
{
#ifdef DEBUG
	if (std::fabs(s) < DivideByZeroTolerance) {
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
			<< "Division by zero" << std::endl;
		return mat3();
	}
#endif

	GEfloat r = GEfloat(1.0) / s;
	return *this * r;
}

mat3 mat3::operator * (const mat3& m) const
{
	mat3 a(0.0);
	int i;
	int j;
	int k;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				a[i][j] += _m[i][k] * m[k][j];

	return a;
}

mat3 mat3::operator >> (const mat3& m) const
{
	// applies m then applies this
	return *this * m;
}

mat3 mat3::operator << (const mat3& m) const
{
	// applies this then applies m
	return m * *this;
}

mat3& mat3::operator += (const mat3& m)
{
	_m[0] += m[0];
	_m[1] += m[1];
	_m[2] += m[2];
	return *this;
}

mat3& mat3::operator -= (const mat3& m)
{
	_m[0] -= m[0];
	_m[1] -= m[1];
	_m[2] -= m[2];
	return *this;
}

mat3& mat3::operator *= (const GEfloat s)
{
	_m[0] *= s;
	_m[1] *= s;
	_m[2] *= s;
	return *this;
}

mat3& mat3::operator *= (const mat3& m)
{
	mat3 a(0.0);
	int i;
	int j;
	int k;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				a[i][j] += _m[i][k] * m[k][j];
	return *this = a;
}

mat3& mat3::operator /= (const GEfloat s)
{
#ifdef DEBUG
	if (std::fabs(s) < DivideByZeroTolerance) {
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
			<< "Division by zero" << std::endl;
		return mat3();
	}
#endif
	GEfloat r = GEfloat(1.0) / s;
	return *this *= r;
}

mat3& mat3::operator <<= (const mat3& m)
{
	return *this *= m;
}

mat3& mat3::operator >>= (const mat3& m)
{
	return (*this = (m * *this));
}

mat3::operator const GEfloat* () const
{
	return static_cast<const GEfloat*>(&_m[0].x);
}

mat3::operator GEfloat* ()
{
	return static_cast<GEfloat*>(&_m[0].x);
}


//
//
// 4D Matrix
//
//

mat4::mat4(const GEfloat d)
{
	_m[0][0] = d;
	_m[1][1] = d;
	_m[2][2] = d;
	_m[3][3] = d;
}

mat4::mat4(const vec4& i, const vec4& j, const vec4& k, const vec4& l)
{
	_m[0] = i;
	_m[1] = j;
	_m[2] = k;
	_m[3] = l;
}

mat4::mat4(GEfloat m00, GEfloat m01, GEfloat m02, GEfloat m03,
		   GEfloat m10, GEfloat m11, GEfloat m12, GEfloat m13,
		   GEfloat m20, GEfloat m21, GEfloat m22, GEfloat m23,
		   GEfloat m30, GEfloat m31, GEfloat m32, GEfloat m33)
{
	_m[0] = vec4(m00, m10, m20, m30);
	_m[1] = vec4(m01, m11, m21, m31);
	_m[2] = vec4(m02, m12, m22, m32);
	_m[3] = vec4(m03, m13, m23, m33);
}

mat4::mat4(const mat4& m)
{
	if (*this != m)
	{
		_m[0] = m[0];
		_m[1] = m[1];
		_m[2] = m[2];
		_m[3] = m[3];
	}
}

vec4& mat4::operator [] (int i)
{
	return _m[i];
}

const vec4& mat4::operator [] (int i) const
{
	return _m[i];
}

mat4 mat4::operator + (const mat4& m) const
{
	return mat4(_m[0] + m[0], _m[1] + m[1], _m[2] + m[2], _m[3] + m[3]);
}

mat4 mat4::operator - (const mat4& m) const
{
	return mat4(_m[0] - m[0], _m[1] - m[1], _m[2] - m[2], _m[3] - m[3]);
}

mat4 mat4::operator * (const GEfloat s) const
{
	return mat4(s * _m[0], s * _m[1], s * _m[2], s * _m[3]);
}

mat4 mat4::operator / (const GEfloat s) const
{
#ifdef DEBUG
	if (std::fabs(s) < DivideByZeroTolerance) {
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
			<< "Division by zero" << std::endl;
		return mat4();
	}
#endif
	GEfloat r = GEfloat(1.0) / s;
	return *this * r;
}

mat4 mat4::operator * (const mat4& m) const
{
	mat4 a(0.0);
	int i;
	int j;
	int k;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			for (k = 0; k < 4; k++)
				a[i][j] += _m[i][k] * m[k][j];
	return a;
}

mat4 mat4::operator >> (const mat4& m) const
{
	// applies m then applies this
	return *this * m;
}

mat4 mat4::operator << (const mat4& m) const
{
	// applies this then applies m
	return m * *this;
}

mat4& mat4::operator += (const mat4& m)
{
	_m[0] += m[0];
	_m[1] += m[1];
	_m[2] += m[2];
	_m[3] += m[3];
	return *this;
}

mat4& mat4::operator -= (const mat4& m)
{
	_m[0] -= m[0];
	_m[1] -= m[1];
	_m[2] -= m[2];
	_m[3] -= m[3];
	return *this;
}

mat4& mat4::operator *= (const GEfloat s)
{
	_m[0] *= s;
	_m[1] *= s;
	_m[2] *= s;
	_m[3] *= s;
	return *this;
}

mat4& mat4::operator *= (const mat4& m)
{
	mat4 a(0.0);
	int i;
	int j;
	int k;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			for (k = 0; k < 4; k++)
				a[i][j] += _m[i][k] * m[k][j];
	return *this = a;
}

mat4& mat4::operator /= (const GEfloat s)
{
#ifdef DEBUG
	if (std::fabs(s) < DivideByZeroTolerance) {
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
			<< "Division by zero" << std::endl;
		return mat4();
	}
#endif
	GEfloat r = GEfloat(1.0) / s;
	return *this *= r;
}

mat4& mat4::operator <<= (const mat4& m)
{
	return *this *= m;
}

mat4& mat4::operator >>= (const mat4& m)
{
	return (*this = (m * *this));
}

vec4 mat4::operator * (const vec4& v) const
{
	return vec4(_m[0][0] * v.x + _m[0][1] * v.y + _m[0][2] * v.z + _m[0][3] * v.w,
				_m[1][0] * v.x + _m[1][1] * v.y + _m[1][2] * v.z + _m[1][3] * v.w,
				_m[2][0] * v.x + _m[2][1] * v.y + _m[2][2] * v.z + _m[2][3] * v.w,
				_m[3][0] * v.x + _m[3][1] * v.y + _m[3][2] * v.z + _m[3][3] * v.w);
}

mat4::operator const GEfloat* () const
{
	return static_cast<const GEfloat*>(&_m[0].x);
}

mat4::operator GEfloat* ()
{
	return static_cast<GEfloat*>(&_m[0].x);
}