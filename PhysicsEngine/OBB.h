#pragma once
#include "Vec3.h"
#include "Matrix3.h"


class OBB
{
public:
	Point3D origin;
	Vec3 size;
	Matrix3 orientation;


public:
	OBB();
	OBB(const Point3D& _origin, const Vec3& _size);
	OBB(const Point3D& _origin, const Vec3& _size, const Matrix3& _orientation);
	~OBB();
};

