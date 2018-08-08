#pragma once
#include "Vec3.h"

class Ray
{
public:
	Point3D origin;
	Vec3 direction;

	static Ray FromPoints(const Point3D& _from, const Point3D& _to);

public:
	Ray();
	Ray(const Point3D& _origin, const Vec3& _direction);
	~Ray();
};

