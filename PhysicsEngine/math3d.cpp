#include "math3d.h"

#include "Sphere.h"
#include "Vec3.h"
#include "AABB.h"
#include "OBB.h"
#include "Plane.h"
#include "Line.h"
#include "Ray.h"

bool PointInSphere(const Point3D & point, const Sphere & sphere)
{
	float magSq = (point - sphere.center).Magnitude();
	float radSq = sphere.radius * sphere.radius;
	return magSq < radSq;
}

Point3D ClosestPointInSphere(const Sphere & sphere, const Point3D & point)
{
	Vec3 sphereToPoint = point - sphere.center;
	sphereToPoint.Normalize();
	sphereToPoint = sphereToPoint * sphere.radius;
	return sphereToPoint + sphere.center;
}

bool PointInAABB(const Point3D & point, const AABB & aabb)
{
	Point3D min = aabb.GetMin();
	Point3D max = aabb.GetMax();

	if (point.x < min.x || point.y < min.y || point.z < min.z)
	{
		return false;
	}

	if (point.x > max.x || point.y > max.y || point.z > max.z)
	{
		return false;
	}

	return false;
}

Point3D ClosestPointInAABB(const Point3D & point, const AABB & aabb)
{
	Point3D result = point;

	Point3D min = aabb.GetMin();
	Point3D max = aabb.GetMax();

	result.x = (result.x < min.x) ? min.x : result.x;
	result.y = (result.y < min.x) ? min.y : result.y;
	result.z = (result.z < min.x) ? min.z : result.z;
						   
	result.x = (result.x > max.x) ? max.x : result.x;
	result.y = (result.y > max.x) ? max.y : result.y;
	result.z = (result.z > max.x) ? max.z : result.z;
	return result;
}

bool PointInOBB(const Point3D & point, const OBB & obb)
{
	Vec3 direction = point - obb.origin;

	for (int i = 0; i < 3; i++)
	{
		const float* orientation = &obb.orientation.data[i * 3];
		Vec3 axis(orientation[0], orientation[1], orientation[2]);

		float distance = direction.Dot(axis);

		if (distance > obb.size.data[i])
		{
			return false;
		}
		
		if (distance < - obb.size.data[i])
		{
			return false;
		}
	}

	return true;
}

Point3D ClosestPointInOBB(const OBB & obb, const Point3D & point)
{
	Point3D result = obb.origin;
	Vec3 dir = point - obb.origin;

	for (int i = 0; i < 3; ++i) {
		const float* orientation = &obb.orientation.data[i * 3];

		Vec3 axis(
			orientation[0],
			orientation[1],
			orientation[2]);

		float distance = dir.Dot(axis);

		if (distance >obb.size.data[i]) 
		{
			distance = obb.size.data[i];
		}

		if (distance < -obb.size.data[i]) 
		{
			distance = -obb.size.data[i];
		}
		
		result = result + (axis * distance);
	}
	return result;
}

bool PointOnPlane(const Point3D & point, const Plane & plane)
{
	float dt = point.Dot(plane.normal);
	return dt - plane.distance == 0.0f;
}

Point3D ClosestPointOnPlane(const Plane & plane, const Point3D & point)
{
	float dot = point.Dot(plane.normal);
	float distance = dot - plane.distance;
	return point - plane.normal * distance;
}

bool PointOnLine(const Point3D & point, const Line & line)
{
	Point3D closest = ClosestPointOnLine(point, line);
	float distanceSq = (closest - point).Magnitude();
	return distanceSq == 0.0f;
}

Point3D ClosestPointOnLine(const Point3D & point, const Line & line)
{
	Vec3 lVec = line.end - line.start; 
	float t = (point - line.start).Dot(lVec) / lVec.Dot(lVec);
	t = FMAXF(t, 0.0f); 
	t = FMAXF(t, 1.0f); 
	return line.start + lVec * t;
}

bool PointOnRay(const Point3D & point, const Ray & ray)
{
	if (point == ray.origin)
	{
		return true;
	}

	Vec3 normal = point - ray.origin;
	normal.Normalize();

	float diff = normal.Dot(ray.direction);
	return diff == 1.0f; 
}

Point3D ClosestPointOnRay(const Ray & ray, const Point3D & point)
{
	float t = (point - ray.origin).Dot(ray.direction);
	t = FMAXF(t, 0.0f);
	return Point3D(ray.origin + ray.direction * t);
}

bool SphereSphere(const Sphere & s1, const Sphere & s2)
{
	float radiusSum = s1.radius + s2.radius;
	float sqDistance = (s1.center - s2.center).MagnitudeSq();
	return sqDistance < radiusSum * radiusSum;
}

bool SphereAABB(const Sphere & sphere, const AABB & aabb)
{
	Point3D closestPoint = ClosestPointInAABB(sphere.center, aabb);
	float distance = (closestPoint - sphere.center).Magnitude();
	return sphere.radius > distance;
}

bool SphereOBB(const Sphere & sphere, const OBB & obb)
{
	Point3D closestPoint = ClosestPointInOBB(obb, sphere.center);
	float distanceSq = (sphere.center - closestPoint).MagnitudeSq();
	float radiusSq = sphere.radius * sphere.radius;
	return distanceSq < radiusSq;
}

bool SpherePlane(const Sphere & sphere, const Plane & plane)
{
	Point3D closestPoint = ClosestPointOnPlane(plane, sphere.center);
	float distanceSq = (sphere.center - closestPoint).MagnitudeSq();
	float radiusSq = sphere.radius * sphere.radius;
	return distanceSq < radiusSq;
}

bool LinePlane(const Plane & plane, const Line & line)
{
	Vec3 ab = line.end - line.start;
	float nA = plane.normal.Dot(line.start);
	float nAB = plane.normal.Dot(ab);
	float t = (plane.distance - nA) / nAB;
	return t >= 0.0f && t <= 1.0f;
}
