#pragma once

#include "Interval.h"

#include "Sphere.h"
#include "Vec3.h"
#include "AABB.h"
#include "OBB.h"
#include "Plane.h"
#include "Line.h"
#include "Ray.h"
#include "Triangle.h"


bool PointInSphere(const Point3D& point, const Sphere& sphere);
Point3D ClosestPointInSphere(const Sphere& sphere, const Point3D& point);

bool PointInAABB(const Point3D& point, const AABB& aabb);
Point3D ClosestPointInAABB(const Point3D& point, const AABB& aabb);

bool PointInOBB(const Point3D& point, const OBB& obb);
Point3D ClosestPointInOBB(const OBB& obb, const Point3D& point);

bool PointOnPlane(const Point3D& point, const Plane& plane);
Point3D ClosestPointOnPlane(const Plane& plane, const Point3D& point);

bool PointOnLine(const Point3D& point, const Line& line);
Point3D ClosestPointOnLine(const Point3D& point, const Line& line);

bool PointOnRay(const Point3D& point, const Ray& ray);
Point3D ClosestPointOnRay(const Ray& ray, const Point3D& point);

bool SphereSphere(const Sphere& s1, const Sphere& s2);
bool SphereAABB(const Sphere& sphere, const AABB& aabb);
bool SphereOBB(const Sphere& sphere, const OBB& obb);
bool SpherePlane(const Sphere& sphere, const Plane& plane);
bool AABBAABB(const AABB& aabb1, const AABB& aabb2);
Interval2D GetInterval(const AABB& aabb, const Vec3& axis);
Interval2D GetInterval(const OBB& obb, const Vec3& axis);
bool OverlapOnAxis(const AABB& aabb, const OBB& obb, const Vec3& axis);
bool OverlapOnAxis(const OBB& obb1, const OBB& obb2, const Vec3& axis);
bool AABBOBB(const AABB& aabb, const OBB& obb);
bool AABBPlane(const AABB& aabb, const Plane& plane);
bool OBBOBB(const OBB& obb1, const OBB& obb2);
bool OBBPlane(const OBB& obb, const Plane& plane);
bool PlanePlane(const Plane& plane1, const Plane& plane2);

float RayCast(const Sphere& sphere, const Ray& ray);
float RayCast(const AABB& aabb, const Ray& ray);
float RayCast(const OBB& obb, const Ray& ray);
float RayCast(const Plane& plane, const Ray& ray);

bool Linetest(const Sphere& sphere, const Line& line);
bool Linetest(const OBB& obb, const Line& line);
bool Linetest(const AABB& aabb, const Line& line);
bool Linetest(const Plane& plane, const Line& line);

bool PointInTriangle(const Point3D& point, const Triangle& triangle);
Plane FromTriangle(const Triangle& triangle);
Point3D ClosestPointInTriangle(const Triangle& triangle, const Point3D& point);
bool TriangleShpere(const Triangle& triangle, const Sphere& sphere);

Interval2D GetInterval(const Triangle& triangle, const Vec3& axis);
bool OverlapOnAxis(const Triangle& triangle, const AABB& aabb, const Vec3& axis);
bool TriangleAABB(const Triangle& triangle, const AABB& aabb);
bool OverlapOnAxis(const OBB& obb, const Triangle& triangle, const Vec3& axis);
bool TriangleOBB(const Triangle& triangle, const OBB& obb);
bool TrianglePlane(const Triangle& triangle, const Plane& plane);
bool OverlapOnAxis(const Triangle& t1, const Triangle& t2, const Vec3& axis);
bool TriangleTriangle(const Triangle& t1, const Triangle& t2);

bool Linetest(const Triangle& triangle, const Line& line);
Vec3 Barycentric(const Point3D& point, const Triangle& triangle);























