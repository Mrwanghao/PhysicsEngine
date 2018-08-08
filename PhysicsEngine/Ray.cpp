#include "Ray.h"



Ray Ray::FromPoints(const Point3D & _from, const Point3D & _to)
{
	return Ray(_from, (_to - _from).GetNormalized());
}

Ray::Ray()
	:
	origin(0.0f, 0.0f, 0.0f),
	direction(0.0f, 0.0f, 1.0f)
{
}

Ray::Ray(const Point3D & _origin, const Vec3 & _direction)
	:
	origin(_origin),
	direction(_direction)
{
	direction.Normalize();
}


Ray::~Ray()
{
}
