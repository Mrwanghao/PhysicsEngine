#pragma once
#include "Matrix4.h"

class Vec3
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float data[3];
	};

public:
	inline float& operator[](int index) { return data[index]; }
	Vec3 operator+(const Vec3& right) const;
	Vec3 operator-(const Vec3& right) const;
	Vec3 operator*(const Vec3& right) const;
	Vec3 operator*(float scale) const;
	bool operator==(const Vec3& right) const;
	bool operator!=(const Vec3& right) const;
	Vec3 operator*(const Matrix4& mat) const;
public:
	Vec3();
	Vec3(float _x, float _y, float _z);

public:
	float Dot(const Vec3& right) const;
	float Magnitude() const;
	float MagnitudeSq() const;
	void Normalize();
	Vec3 GetNormalized() const;
	Vec3 Cross(const Vec3& right) const;
	float Angle(const Vec3& right) const;

	Vec3 Project(const Vec3& right);
};

typedef Vec3 Point3D;