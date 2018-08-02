#include "Vec2.h"
#include <math.h>



Vec2 Vec2::operator+(const Vec2 & right) const
{
	return Vec2(x + right.x, y + right.y);
}

Vec2 Vec2::operator-(const Vec2 & right) const
{
	return Vec2(x - right.x, y - right.y);
}

Vec2 Vec2::operator*(const Vec2 & right) const
{
	return Vec2(x * right.x, y * right.y);
}

Vec2 Vec2::operator*(float scale) const
{
	return Vec2(x * scale, y * scale);
}

bool Vec2::operator==(const Vec2 & right)
{
	return x == right.x && y == right.y;
}

bool Vec2::operator!=(const Vec2 & right)
{
	return !(*this == right);
}

Vec2 Vec2::operator*(const Matrix2 & right)
{
	Vec2 result;
	float temp = 0.0f;
	
	for (int j = 0; j < 2; j++)
	{
		temp = 0.0f;
		for (int index = 0; index < 2; index++)
		{
			temp += data[index] * right.data[index * 2 + j];
		}
		result.data[j] = temp;
	}
		
	return result;
}

Vec2::Vec2()
	:
	x(0.0f),
	y(0.0f)
{
}

Vec2::Vec2(float _x, float _y)
	:
	x(_x),
	y(_y)
{
}

float Vec2::Dot(const Vec2 & right) const
{
	return x * right.x + y * right.y;
}

float Vec2::Magnitude() const
{
	return sqrtf(x * x + y * y);
}

float Vec2::MagnitudeSq() const
{
	return x * x + y * y;
}

float Vec2::Distance(const Vec2 & right) const
{
	Vec2 t = right - *this;
	return (right - *this).Magnitude();
}

void Vec2::Normalize()
{
	float length = Magnitude();
	if (length == 0) return;
	x /= length;
	y /= length;
}

Vec2 Vec2::GetNormalized() const
{
	float length = Magnitude();
	if (length == 0) return *this;
	Vec2 result;
	result.x = x / length;
	result.y = y / length;
	return result;
}

float Vec2::Angle(const Vec2 & right) const
{
	float m = Magnitude() * right.Magnitude();
	return acos(Dot(right) / m);
}
