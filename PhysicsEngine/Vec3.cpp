#include "Vec3.h"
#include <math.h>

typedef Vec3 Point3D;

Vec3 Vec3::operator+(const Vec3 & right) const
{
	return Vec3(x + right.x, y + right.y, z + right.z);
}

Vec3 Vec3::operator-(const Vec3 & right) const
{
	return Vec3(x - right.x, y - right.y, z - right.z);
}

Vec3 Vec3::operator*(const Vec3 & right) const
{
	return Vec3(x * right.x, y * right.y, z * right.z);
}

Vec3 Vec3::operator*(float scale) const
{
	return Vec3(x * scale, y * scale, z * scale);
}

bool Vec3::operator==(const Vec3 & right)
{
	return x == right.x && y == right.y && z == right.z;
}

bool Vec3::operator!=(const Vec3 & right)
{
	return !(*this == right);
}

Vec3::Vec3()
	:
	x(0.0f),
	y(0.0f),
	z(0.0f)
{
}

Vec3::Vec3(float _x, float _y, float _z)
	:
	x(_x),
	y(_y),
	z(_z)
{
}

float Vec3::Dot(const Vec3 & right) const
{
	return x * right.x + y * right.y + z * right.z;
}

float Vec3::Magnitude() const
{
	return sqrtf(x * x + y * y + z * z);
}

float Vec3::MagnitudeSq() const
{
	return x * x + y * y + z * z;
}

void Vec3::Normalize()
{
	float length = Magnitude();
	if (length == 0) return;
	x /= length;
	y /= length;
	z /= length;
}

Vec3 Vec3::GetNormalized() const
{
	float length = Magnitude();
	if (length == 0) return *this;
	Vec3 result;
	result.x = x / length;
	result.y = y / length;
	result.z = z / length;
	return result;
}

Vec3 Vec3::Cross(const Vec3 & right) const
{
	Vec3 result;
	result.x = y * right.z - z * right.y;
	result.y = z * right.x - x * right.z;
	result.z = x * right.y - y * right.x;
	return result;
}

float Vec3::Angle(const Vec3 & right) const
{
	float m = Magnitude() * right.Magnitude();
	return acos(Dot(right) / m);
}
