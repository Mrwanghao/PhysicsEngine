#include "Vec4.h"
#include <math.h>


typedef Vec4 Point4D;

Vec4 Vec4::operator+(const Vec4 & right) const
{
	return Vec4(x + right.x, y + right.y, z + right.z, w + right.w);
}

Vec4 Vec4::operator-(const Vec4 & right) const
{
	return Vec4(x - right.x, y - right.y, z - right.z, w - right.w);
}

Vec4 Vec4::operator*(const Vec4 & right) const
{
	return Vec4(x * right.x, y * right.y, z * right.z, w * right.w);
}

Vec4 Vec4::operator*(float scale) const
{
	return Vec4(x * scale, y * scale, z * scale, w * scale);
}

bool Vec4::operator==(const Vec4 & right)
{
	return x == right.x && y == right.y && z == right.z && w == right.w;
}

bool Vec4::operator!=(const Vec4 & right)
{
	return !(*this == right);
}

Vec4::Vec4()
	:
	x(0.0f),
	y(0.0f),
	z(0.0f),
	w(0.0f)
{
}

Vec4::Vec4(float _x, float _y, float _z, float _w)
	:
	x(_x),
	y(_y),
	z(_z),
	w(_w)
{
}

float Vec4::Dot(const Vec4& right) const
{
	return x * right.x + y * right.y + z * right.z + w * right.w;
}

float Vec4::Magnitude() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

float Vec4::MagnitudeSq() const
{
	return x * x + y * y + z * z + w * w;
}

void Vec4::Normalize()
{
	float length = Magnitude();
	if (length == 0) return;
	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

Vec4 Vec4::GetNormalized() const
{
	float length = Magnitude();
	if (length == 0) return *this;
	Vec4 result;
	result.x = x / length;
	result.y = y / length;
	result.z = z / length;
	result.w = w / length;
	return result;
}
