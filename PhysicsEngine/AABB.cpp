#include "AABB.h"
#include "MathUtil.h"


Vec3 AABB::GetMin() const
{
	Vec3 p1 = origin + size;
	Vec3 p2 = origin - size;

	return Vec3(FMINF(p1.x, p2.x), FMINF(p1.y, p2.y), FMINF(p1.z, p2.z));
}

Vec3 AABB::GetMax() const
{
	Vec3 p1 = origin + size;
	Vec3 p2 = origin - size;

	return Vec3(FMAXF(p1.x, p2.x), FMAXF(p1.y, p2.y), FMAXF(p1.z, p2.z));
}

AABB AABB::FromMinMax(const Vec3 & _min, const Vec3 & _max)
{
	return AABB((_min + _max) * 0.5f, (_max - _min) * 0.5f);
}

AABB::AABB()
	:
	size(1.0f, 1.0f, 1.0f)
{
}

AABB::AABB(const Point3D & _origin, const Vec3 & _size)
	:
	origin(_origin),
	size(_size)
{
}


AABB::~AABB()
{
}
