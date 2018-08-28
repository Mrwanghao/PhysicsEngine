#include "Frustum.h"

bool Intersects(const Frustum & f, const Point3D & p)
{
	for (int i = 0; i < 6; i++)
	{
		Vec3 normal = f.planes[i].normal;
		float distance = f.planes[i].distance;
		float side = p.Dot(normal) - distance;
		if (side < 0.0f)
			return false;
	}
	return true;
}

bool Intersects(const Frustum & f, const Sphere & s)
{
	for (int i = 0; i < 6; i++)
	{
		Vec3 normal = f.planes[i].normal;
		float distance = f.planes[i].distance;
		float side = s.center.Dot(normal) - distance;
		if (side < -s.radius)
			return false;
	}
	return true;
}
