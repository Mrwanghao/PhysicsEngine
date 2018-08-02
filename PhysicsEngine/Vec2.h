#pragma once

#include "Matrix2.h"

class Vec2
{
public:
	union
	{
		struct
		{
			float x;
			float y;
		};
		float data[2];
	};

public:
	inline float& operator[](int index) { return data[index]; }
	Vec2 operator+(const Vec2& right) const;
	Vec2 operator-(const Vec2& right) const;
	Vec2 operator*(const Vec2& right) const;
	Vec2 operator*(float scale) const;
	bool operator==(const Vec2& right);
	bool operator!=(const Vec2& right);
	Vec2 operator*(const Matrix2& right);

public:
	Vec2();
	Vec2(float _x, float _y);

public:
	float Dot(const Vec2& right) const;
	float Magnitude() const;
	float MagnitudeSq() const;
	float Distance(const Vec2& right) const;
	void Normalize();
	Vec2 GetNormalized() const;
	float Angle(const Vec2& right) const;
};

typedef Vec2 Point2D;