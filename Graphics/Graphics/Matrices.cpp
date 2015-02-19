#include "Matrices.h"

using namespace graphics;

//
//
// 2D Matrix
//
//

Mat2::Mat2(const GEfloat d)
{
	_m[0][0] = d;
	_m[1][1] = d;
}

Mat2::Mat2(const Vec2& i, const Vec2& j)
{
	_m[0] = i;
	_m[2] = j;
}

Mat2::Mat2(GEfloat m00, GEfloat m01,
		   GEfloat m10, GEfloat m11)
{
	_m[0] = Vec2(m00, m10);
	_m[1] = Vec2(m01, m11);
}

Mat2::Mat2(const Mat2& m)
{
	if (*this != m)
	{
		_m[0] = m[0];
		_m[1] = m[1];
	}
}

Vec2& Mat2::operator[] (int i)
{
	return _m[i];
}

const Vec2& Mat2::operator [] (int i) const
{
	return _m[i];
}

Mat2 Mat2::operator + (const Mat2& m) const
{
	return Mat2(_m[0] + m[0], _m[1] + m[1]);
}

Mat2 Mat2::operator - (const Mat2& m) const
{
	return Mat2(_m[0] - m[0], _m[1] - m[1]);
}

Mat2 Mat2::operator * (const GEfloat s) const
{
	return Mat2(s*_m[0], s*_m[1]);
}

Mat2 Mat2::operator / (const GEfloat s) const
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

Mat2 Mat2::operator * (const Mat2& m) const
{
	Mat2 a(0.0);
	int i;
	int j;
	int k;

	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			for (k = 0; k < 2; k++)
				a[i][j] += _m[i][k] * m[k][j];
	return a;
}

Mat2 Mat2::operator >> (const Mat2& m) const
{
	// applies m then applies this
	return *this * m;
}

Mat2 Mat2::operator << (const Mat2& m) const
{
	// applies this then applies m
	return m * *this;
}

Mat2& Mat2::operator += (const Mat2& m)
{
	_m[0] += m[0];
	_m[1] += m[1];
	return *this;
}

Mat2& Mat2::operator -= (const Mat2& m)
{
	_m[0] -= m[0];
	_m[1] -= m[1];
	return *this;
}

Mat2& Mat2::operator *= (const GEfloat s)
{
	_m[0] *= s;
	_m[1] *= s;
	return *this;
}

Mat2& Mat2::operator *= (const Mat2& m)
{
	Mat2 a(0.0);
	int i;
	int j;
	int k;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 2; j++)
			for (k = 0; k < 2; k++)
				a[i][j] += _m[i][k] * m[k][j];
	return *this = a;
}

Mat2& Mat2::operator /= (const GEfloat s)
{
#ifdef DEBUG
	if (std::fabs(s) < DivideByZeroTolerance) {
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
			<< "Division by zero" << std::endl;
		return Mat2();
	}
#endif
	GEfloat r = GEfloat(1.0) / s;
	return *this *= r;
}

Vec2 Mat2::operator * (const Vec2& v) const
{
	return Vec2(_m[0][0] * v.x + _m[0][1] * v.y,
				_m[1][0] * v.x + _m[1][1] * v.y);
}

Mat2& Mat2::operator <<= (const Mat2& m)
{
	return *this *= m;
}

Mat2& Mat2::operator >>= (const Mat2& m)
{
	return (*this = (m * *this));
}

Mat2::operator const GEfloat* () const
{
	return static_cast<const GEfloat*>(&_m[0].x);
}

Mat2::operator GEfloat* ()
{
	return static_cast<GEfloat*>(&_m[0].x);
}


//
//
// 3D Matrix
//
//

Mat3::Mat3(const GEfloat d)
{
	_m[0][0] = d;
	_m[1][1] = d;
	_m[2][2] = d;
}

Mat3::Mat3(const Vec3& i, const Vec3& j, const Vec3& k)
{
	_m[0] = i;
	_m[1] = j;
	_m[2] = k;
}

Mat3::Mat3(GEfloat m00, GEfloat m01, GEfloat m02,
		   GEfloat m10, GEfloat m11, GEfloat m12,
		   GEfloat m20, GEfloat m21, GEfloat m22)
{
	_m[0] = Vec3(m00, m10, m20);
	_m[1] = Vec3(m01, m11, m12);
	_m[2] = Vec3(m02, m12, m22);
}

Mat3::Mat3(const Mat3& m)
{
	if (*this != m)
	{
		_m[0] = m[0];
		_m[1] = m[1];
		_m[2] = m[2];
	}
}

Vec3& Mat3::operator [] (int i)
{
	return _m[i];
}

const Vec3& Mat3::operator [] (int i) const
{
	return _m[i];
}

Mat3 Mat3::operator + (const Mat3& m) const
{
	return Mat3(_m[0] + m[0], _m[1] + m[1], _m[2] + m[2]);
}

Mat3 Mat3::operator - (const Mat3& m) const
{
	return Mat3(_m[0] - m[0], _m[1] - m[1], _m[2] - m[2]);
}

Mat3 Mat3::operator * (const GEfloat s) const
{
	return Mat3(s * _m[0], s * _m[1], s * _m[2]);
}

Mat3 Mat3::operator / (const GEfloat s) const
{
#ifdef DEBUG
	if (std::fabs(s) < DivideByZeroTolerance) {
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
			<< "Division by zero" << std::endl;
		return Mat3();
	}
#endif

	GEfloat r = GEfloat(1.0) / s;
	return *this * r;
}

Mat3 Mat3::operator * (const Mat3& m) const
{
	Mat3 a(0.0);
	int i;
	int j;
	int k;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				a[i][j] += _m[i][k] * m[k][j];

	return a;
}

Mat3 Mat3::operator >> (const Mat3& m) const
{
	// applies m then applies this
	return *this * m;
}

Mat3 Mat3::operator << (const Mat3& m) const
{
	// applies this then applies m
	return m * *this;
}

Mat3& Mat3::operator += (const Mat3& m)
{
	_m[0] += m[0];
	_m[1] += m[1];
	_m[2] += m[2];
	return *this;
}

Mat3& Mat3::operator -= (const Mat3& m)
{
	_m[0] -= m[0];
	_m[1] -= m[1];
	_m[2] -= m[2];
	return *this;
}

Mat3& Mat3::operator *= (const GEfloat s)
{
	_m[0] *= s;
	_m[1] *= s;
	_m[2] *= s;
	return *this;
}

Mat3& Mat3::operator *= (const Mat3& m)
{
	Mat3 a(0.0);
	int i;
	int j;
	int k;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				a[i][j] += _m[i][k] * m[k][j];
	return *this = a;
}

Mat3& Mat3::operator /= (const GEfloat s)
{
#ifdef DEBUG
	if (std::fabs(s) < DivideByZeroTolerance) {
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
			<< "Division by zero" << std::endl;
		return Mat3();
	}
#endif
	GEfloat r = GEfloat(1.0) / s;
	return *this *= r;
}

Mat3& Mat3::operator <<= (const Mat3& m)
{
	return *this *= m;
}

Mat3& Mat3::operator >>= (const Mat3& m)
{
	return (*this = (m * *this));
}

Mat3::operator const GEfloat* () const
{
	return static_cast<const GEfloat*>(&_m[0].x);
}

Mat3::operator GEfloat* ()
{
	return static_cast<GEfloat*>(&_m[0].x);
}


//
//
// 4D Matrix
//
//

Mat4::Mat4(const GEfloat d)
{
	_m[0][0] = d;
	_m[1][1] = d;
	_m[2][2] = d;
	_m[3][3] = d;
}

Mat4::Mat4(const Vec4& i, const Vec4& j, const Vec4& k, const Vec4& l)
{
	_m[0] = i;
	_m[1] = j;
	_m[2] = k;
	_m[3] = l;
}

Mat4::Mat4(GEfloat m00, GEfloat m01, GEfloat m02, GEfloat m03,
		   GEfloat m10, GEfloat m11, GEfloat m12, GEfloat m13,
		   GEfloat m20, GEfloat m21, GEfloat m22, GEfloat m23,
		   GEfloat m30, GEfloat m31, GEfloat m32, GEfloat m33)
{
	_m[0] = Vec4(m00, m10, m20, m30);
	_m[1] = Vec4(m01, m11, m21, m31);
	_m[2] = Vec4(m02, m12, m22, m32);
	_m[3] = Vec4(m03, m13, m23, m33);
}

Mat4::Mat4(const Mat4& m)
{
	if (*this != m)
	{
		_m[0] = m[0];
		_m[1] = m[1];
		_m[2] = m[2];
		_m[3] = m[3];
	}
}

Vec4& Mat4::operator [] (int i)
{
	return _m[i];
}

const Vec4& Mat4::operator [] (int i) const
{
	return _m[i];
}

Mat4 Mat4::operator + (const Mat4& m) const
{
	return Mat4(_m[0] + m[0], _m[1] + m[1], _m[2] + m[2], _m[3] + m[3]);
}

Mat4 Mat4::operator - (const Mat4& m) const
{
	return Mat4(_m[0] - m[0], _m[1] - m[1], _m[2] - m[2], _m[3] - m[3]);
}

Mat4 Mat4::operator * (const GEfloat s) const
{
	return Mat4(s * _m[0], s * _m[1], s * _m[2], s * _m[3]);
}

Mat4 Mat4::operator / (const GEfloat s) const
{
#ifdef DEBUG
	if (std::fabs(s) < DivideByZeroTolerance) {
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
			<< "Division by zero" << std::endl;
		return Mat4();
	}
#endif
	GEfloat r = GEfloat(1.0) / s;
	return *this * r;
}

Mat4 Mat4::operator * (const Mat4& m) const
{
	Mat4 a(0.0);
	int i;
	int j;
	int k;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			for (k = 0; k < 4; k++)
				a[i][j] += _m[i][k] * m[k][j];
	return a;
}

Mat4 Mat4::operator >> (const Mat4& m) const
{
	// applies m then applies this
	return *this * m;
}

Mat4 Mat4::operator << (const Mat4& m) const
{
	// applies this then applies m
	return m * *this;
}

Mat4& Mat4::operator += (const Mat4& m)
{
	_m[0] += m[0];
	_m[1] += m[1];
	_m[2] += m[2];
	_m[3] += m[3];
	return *this;
}

Mat4& Mat4::operator -= (const Mat4& m)
{
	_m[0] -= m[0];
	_m[1] -= m[1];
	_m[2] -= m[2];
	_m[3] -= m[3];
	return *this;
}

Mat4& Mat4::operator *= (const GEfloat s)
{
	_m[0] *= s;
	_m[1] *= s;
	_m[2] *= s;
	_m[3] *= s;
	return *this;
}

Mat4& Mat4::operator *= (const Mat4& m)
{
	Mat4 a(0.0);
	int i;
	int j;
	int k;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			for (k = 0; k < 4; k++)
				a[i][j] += _m[i][k] * m[k][j];
	return *this = a;
}

Mat4& Mat4::operator /= (const GEfloat s)
{
#ifdef DEBUG
	if (std::fabs(s) < DivideByZeroTolerance) {
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
			<< "Division by zero" << std::endl;
		return Mat4();
	}
#endif
	GEfloat r = GEfloat(1.0) / s;
	return *this *= r;
}

Mat4& Mat4::operator <<= (const Mat4& m)
{
	return *this *= m;
}

Mat4& Mat4::operator >>= (const Mat4& m)
{
	return (*this = (m * *this));
}

Vec4 Mat4::operator * (const Vec4& v) const
{
	return Vec4(_m[0][0] * v.x + _m[0][1] * v.y + _m[0][2] * v.z + _m[0][3] * v.w,
				_m[1][0] * v.x + _m[1][1] * v.y + _m[1][2] * v.z + _m[1][3] * v.w,
				_m[2][0] * v.x + _m[2][1] * v.y + _m[2][2] * v.z + _m[2][3] * v.w,
				_m[3][0] * v.x + _m[3][1] * v.y + _m[3][2] * v.z + _m[3][3] * v.w);
}

Mat4::operator const GEfloat* () const
{
	return static_cast<const GEfloat*>(&_m[0].x);
}

Mat4::operator GEfloat* ()
{
	return static_cast<GEfloat*>(&_m[0].x);
}