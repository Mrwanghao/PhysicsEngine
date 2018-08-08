#include "Sphere.h"



Sphere::Sphere()
	:
	radius(1.0f)
{
}

Sphere::Sphere(const Point3D & _center, float _radius)
	:
	center(_center),
	radius(_radius)
{
}


Sphere::~Sphere()
{
}
