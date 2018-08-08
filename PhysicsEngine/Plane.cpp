#include "Plane.h"



Plane::Plane()
	:
	normal(1.0f, 0.0f, 0.0f)
{
}

Plane::Plane(const Vec3 & _normal, float _distance)
	:
	normal(_normal),
	distance(_distance)
{
}


Plane::~Plane()
{
}

float Plane::PlaneEquation(const Point3D & _point)
{
	return _point.Dot(normal) - distance;
}
