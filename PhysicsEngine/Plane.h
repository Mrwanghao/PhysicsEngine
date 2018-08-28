#pragma once
#include "Vec3.h"

class Plane
{
public:
	Vec3 normal;
	float distance;

public:
	Plane();
	Plane(const Vec3& _normal, float _distance);
	~Plane();

	float PlaneEquation(const Point3D& _point) const;
};

