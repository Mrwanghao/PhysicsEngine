#pragma once

#include "Vec3.h"

class Sphere
{
public:
	Point3D center;
	float radius;

public:
	Sphere();
	Sphere(const Point3D& _center, float _radius);
	~Sphere();
};

