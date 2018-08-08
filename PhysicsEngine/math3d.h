#pragma once

class Sphere;
class Vec3;
class AABB;
class OBB;
class Plane;
class Line;
class Ray;

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
