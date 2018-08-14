#include "math3d.h"
#include <math.h>

#include "math2d.h"

float kSholdValue = 0.00001f;

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

bool AABBAABB(const AABB & aabb1, const AABB & aabb2)
{
	Point3D aMin = aabb1.GetMin();
	Point3D aMax = aabb1.GetMax();
	
	Point3D bMin = aabb2.GetMin();
	Point3D bMax = aabb2.GetMax();
	
	return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
	(aMin.y <= bMax.y && aMax.y >= bMin.y) &&
	(aMin.z <= bMax.z && aMax.z >= bMin.z);
}

Interval2D GetInterval(const AABB& aabb, const Vec3& axis)
{
	Vec3 i = aabb.GetMin();
	Vec3 a = aabb.GetMax();
	Vec3 vertex[8] = {
		Vec3(i.x, a.y, a.z),
		Vec3(i.x, a.y, i.z),
		Vec3(i.x, i.y, a.z),
		Vec3(i.x, i.y, i.z),
		Vec3(a.x, a.y, a.z),
		Vec3(a.x, a.y, i.z),
		Vec3(a.x, i.y, a.z),
		Vec3(a.x, i.y, i.z)
	};

	Interval2D result;
	result.min = result.max = axis.Dot(vertex[0]);
	for (int i = 1; i < 8; ++i) {
		float projection = axis.Dot(vertex[i]);
		result.min = (projection < result.min) ?
			projection : result.min;
		result.max = (projection > result.max) ?
			projection : result.max;
	}
	return result;
}

Interval2D GetInterval(const OBB& obb, const Vec3& axis)
{
	Vec3 vertex[8];
	
	Vec3 C = obb.origin; // OBB Center
	Vec3 E = obb.size; // OBB Extents
	const float* o = obb.orientation.data;
	Vec3 A[] = { // OBB Axis
		Vec3(o[0], o[1], o[2]),
		Vec3(o[3], o[4], o[5]),
		Vec3(o[6], o[7], o[8]),
	};
	
	vertex[0] = C + A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	vertex[1] = C - A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	vertex[2] = C + A[0] * E[0] - A[1] * E[1] + A[2] * E[2];
	vertex[3] = C + A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	vertex[4] = C - A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	vertex[5] = C + A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	vertex[6] = C - A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	vertex[7] = C - A[0] * E[0] - A[1] * E[1] + A[2] * E[2];
	
	Interval2D result;
	result.min = result.max = axis.Dot(vertex[0]);
	for (int i = 1; i < 8; ++i) {
		float projection = axis.Dot(vertex[i]);
		result.min = (projection < result.min) ?
			projection : result.min;
		result.max = (projection > result.max) ?
			projection : result.max;
	}
	return result;
}

Interval2D GetInterval(const Triangle& triangle, const Vec3& axis)
{
	Interval2D result;
	
	result.min = axis.Dot(triangle.points[0]);
	result.max = result.min;
	
	for (int i = 1; i < 3; ++i) {
		float value = axis.Dot(triangle.points[i]);
		result.min = fminf(result.min, value);
		result.max = fmaxf(result.max, value);
	}
	return result;
}

bool OverlapOnAxis(const Triangle & triangle, const AABB & aabb, const Vec3 & axis)
{
	Interval2D a = GetInterval(aabb, axis);
	Interval2D b = GetInterval(triangle, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool TriangleAABB(const Triangle & triangle, const AABB & aabb)
{
	Vec3 f0 = triangle.b - triangle.a;
	Vec3 f1 = triangle.c - triangle.b;
	Vec3 f2 = triangle.a - triangle.c;
	
	Vec3 u0(1.0f, 0.0f, 0.0f);
	Vec3 u1(0.0f, 1.0f, 0.0f);
	Vec3 u2(0.0f, 0.0f, 1.0f);
	
	Vec3 test[13] = {
		u0,
		u1,
		u2,
		f0.Cross(f1),
		u0.Cross(f0), u0.Cross(f1), u0.Cross(f2),
		u1.Cross(f0), u1.Cross(f1), u1.Cross(f2),
		u2.Cross(f0), u2.Cross(f1), u2.Cross(f2)
	};
	
	for (int i = 0; i < 13; ++i) {
		if (!OverlapOnAxis(triangle, aabb, test[i])) {
			return false;
		}
	}
	return true; 
}

bool OverlapOnAxis(const OBB & obb, const Triangle & triangle, const Vec3 & axis)
{
	Interval2D a = GetInterval(obb, axis);
	Interval2D b = GetInterval(triangle, axis);
	return ((b.min <= a.max) && (a.min <= b.max));

}

bool TriangleOBB(const Triangle & triangle, const OBB & obb)
{
	Vec3 f0 = triangle.b - triangle.a;
	Vec3 f1 = triangle.c - triangle.b;
	Vec3 f2 = triangle.a - triangle.c;

	const float* orientation = obb.orientation.data;
	Vec3 u0(orientation[0], orientation[1], orientation[2]);
	Vec3 u1(orientation[3], orientation[4], orientation[5]);
	Vec3 u2(orientation[6], orientation[7], orientation[8]);

	Vec3 test[13] = {
		u0, // OBB Axis 1
		u1, // OBB Axis 2
		u2, // OBB Axis 3
		f0.Cross(f1),
		u0.Cross(f0), u0.Cross(f1), u0.Cross(f2),
		u1.Cross(f0), u1.Cross(f1), u1.Cross(f2),
		u2.Cross(f0), u2.Cross(f1), u2.Cross(f2)
	};

	for (int i = 0; i < 13; ++i) {

		if (!OverlapOnAxis(obb, triangle, test[i])) {
			return false;
		}
		return true;
}

bool TrianglePlane(const Triangle & triangle, const Plane & plane);
{
	float side1 = plane.PlaneEquation(triangle.a);
	float side2 = plane.PlaneEquation(triangle.b);
	float side3 = plane.PlaneEquation(triangle.c);
	
	if (side1 == 0 && side2 ==0 && side3 == 0) {
		return true;
	}
	
	if (side1 > 0 && side2 > 0 && side3 > 0) {
		return false;
	}

	if (side1 < 0 && side2 < 0 && side3 < 0) {
		return false;
	}
	
	return true; // Intersection
}

bool OverlapOnAxis(const Triangle & t1, const Triangle & t2, const Vec3 & axis)
{
	Interval2D a = GetInterval(t1, axis);
	Interval2D b = GetInterval(t2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));

}

bool Linetest(const Triangle & triangle, const Line & line)
{
	Ray ray;
	ray.origin = line.start;
	ray.direction = (line.end - line.start).GetNormalized();
	float t = Raycast(triangle, ray);
	return t >= 0 && t * t <= LengthSq(line);
}

Vec3 Barycentric(const Point3D & point, const Triangle & triangle)
{
	return Vec3();
}

bool TriangleTriangle(const Triangle & t1, const Triangle & t2)
{
	Vec3 t1_f0 = t1.b - t1.a;
	Vec3 t1_f1 = t1.c - t1.b;
	Vec3 t1_f2 = t1.a - t1.c;
	
	Vec3 t2_f0 = t2.b - t2.a; 
	Vec3 t2_f1 = t2.c - t2.b; 
	Vec3 t2_f2 = t2.a - t2.c; 

	Vec3 axisToTest[] = {
		t1_f0.Cross(t1_f1),
		t2_f0.Cross(t2_f1),
		t2_f0.Cross(t1_f0), t2_f0.Cross(t1_f1),
		t2_f0.Cross(t1_f2), t2_f1.Cross(t1_f0),
		t2_f1.Cross(t1_f1), t2_f1.Cross(t1_f2),
		t2_f2.Cross(t1_f0), t2_f2.Cross(t1_f1),
		t2_f2.Cross(t1_f2),
	};

	for (int i = 0; i < 11; ++i) {
		if (!OverlapOnAxis(t1, t2, axisToTest[i])) {
			return false; 
		}
	}
	return true; 

bool OverlapOnAxis(const AABB& aabb, const OBB& obb, const Vec3& axis) 
{
	Interval2D a = GetInterval(aabb, axis);
	Interval2D b = GetInterval(obb, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OverlapOnAxis(const OBB& obb1, const OBB& obb2, const Vec3& axis)
{
	Interval2D a = GetInterval(obb1, axis);
	Interval2D b = GetInterval(obb2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool AABBOBB(const AABB& aabb, const OBB& obb)
{
	const float* o = obb.orientation.data;
	Vec3 test[15] = {
		Vec3(1, 0, 0),
		Vec3(0, 1, 0),
		Vec3(0, 0, 1),
		Vec3(o[0], o[1], o[2]),
		Vec3(o[3], o[4], o[5]),
		Vec3(o[6], o[7], o[8])

	};

	for (int i = 0; i < 3; ++i) { // Fill out rest of axis
		test[6 + i * 3 + 0] = test[i + 3].Cross(test[0]);
		test[6 + i * 3 + 1] = test[i + 3].Cross(test[1]);
		test[6 + i * 3 + 2] = test[i + 3].Cross(test[2]);
	}

	for (int i = 0; i < 15; ++i) {
		if (!OverlapOnAxis(aabb, obb, test[i])) {
			return false;
		}
	}
	return true;
}

bool AABBPlane(const AABB & aabb, const Plane & plane)
{
	float pLen = aabb.size.x * fabsf(plane.normal.x) +
		aabb.size.y * fabsf(plane.normal.y) +
		aabb.size.z * fabsf(plane.normal.z);
	
	float dot = plane.normal.Dot(aabb.origin);
	float dist = dot - plane.distance;

	return fabsf(dist) <= pLen;
}

bool OBBOBB(const OBB & obb1, const OBB & obb2)
{
	const float* o1 = obb1.orientation.data;
	const float* o2 = obb2.orientation.data;
	Vec3 test[15] = {
		Vec3(o1[0], o1[1], o1[2]),
		Vec3(o1[3], o1[4], o1[5]),
		Vec3(o1[6], o1[7], o1[8]),
		Vec3(o2[0], o2[1], o2[2]),
		Vec3(o2[3], o2[4], o2[5]),
		Vec3(o2[6], o2[7], o2[8])
	};
	
	for (int i = 0; i < 3; ++i) { // Fill out rest of axis
		test[6 + i * 3 + 0] = test[i + 3].Cross(test[0]);
		test[6 + i * 3 + 1] = test[i + 3].Cross(test[1]);
		test[6 + i * 3 + 2] = test[i + 3].Cross(test[2]);
	}
	
	for (int i = 0; i < 15; ++i) {
		if (!OverlapOnAxis(obb1, obb2, test[i])) {
			return false; 
		}
	}
	return true; 
}

bool OBBPlane(const OBB & obb, const Plane & plane)
{
	const float* o = obb.orientation.data;
	Vec3 rot[] = { // rotation / orientation
		Vec3(o[0], o[1], o[2]),
		Vec3(o[3], o[4], o[5]),
		Vec3(o[6], o[7], o[8]),
	};
	Vec3 normal = plane.normal;
	
	float pLen = obb.size.x * fabsf(normal.Dot(rot[0])) +
		obb.size.y * fabsf(normal.Dot(rot[1])) +
		obb.size.z * fabsf(normal.Dot(rot[2]));

	float dot = plane.normal.Dot(obb.origin);
	float dist = dot - plane.distance;
	
	return fabsf(dist) <= pLen;
}

bool PlanePlane(const Plane & plane1, const Plane & plane2)
{
	Vec3 d = plane1.normal.Cross(plane2.normal);
	return d.Dot(d) != 0; 
}

float RayCast(const Sphere & sphere, const Ray & ray)
{
	Vec3 e = sphere.center - ray.origin;
	float rsq = sphere.radius * sphere.radius;
	float esq = e.MagnitudeSq();

	float a = e.Dot(ray.direction);
	float bsq = esq - a * a;
	float f = sqrtf(rsq - bsq);

	if (rsq - (esq - (a * a)) < 0.0f) 
	{
		return -1; 
	}
	else if (esq<rsq) 
	{
		return a + f; 
	}

	return a - f;
}

float RayCast(const AABB & aabb, const Ray & ray)
{
	Vec3 min = aabb.GetMin();
	Vec3 max = aabb.GetMax();
	
	// NOTE: Any component of direction could be 0!
	// to avoid a division by 0, you need to add
	// additional safety checks.
	float t1;
	float t2;
	float t3;
	float t4;
	float t5;
	float t6;
	if (ray.direction.x != 0.0f)
	{
		t1 = (min.x - ray.origin.x) / ray.direction.x;
		t2 = (max.x - ray.origin.x) / ray.direction.x;
	}
	else
	{
		t1 = (min.x - ray.origin.x) / kSholdValue;
		t2 = (max.x - ray.origin.x) / kSholdValue;
	}

	if (ray.direction.y != 0.0f)
	{
		t3 = (min.y - ray.origin.y) / ray.direction.y;
		t4 = (max.y - ray.origin.y) / ray.direction.y;
	}
	else
	{
		t3 = (min.y - ray.origin.y) / kSholdValue;
		t4 = (max.y - ray.origin.y) / kSholdValue;
	}

	if (ray.direction.z != 0.0f)
	{
		t5 = (min.z - ray.origin.z) / ray.direction.z;
		t6 = (max.z - ray.origin.z) / ray.direction.z;
	}
	else
	{
		t5 = (min.z - ray.origin.z) / kSholdValue;
		t6 = (max.z - ray.origin.z) / kSholdValue;
	}
	
	float tmin = fmaxf(
		fmaxf(
			fminf(t1, t2),
			fminf(t3, t4)
		),
		fminf(t5, t6)
	);
	
	float tmax = fminf(
		fminf(
			fmaxf(t1, t2),
			fmaxf(t3, t4)
		),
		fmaxf(t5, t6)
	);
	
	if (tmax< 0) {
		return -1;
	}
	
	if (tmin>tmax) {
		return -1;
	}
	
	if (tmin< 0.0f) {
		return tmax;
	}
	return tmin;
}


float RayCast(const OBB & obb, const Ray & ray)
{
	const float* o = obb.orientation.data;
	const float* size = obb.size.data;

	Vec3 X(o[0], o[1], o[2]);
	Vec3 Y(o[3], o[4], o[5]);
	Vec3 Z(o[6], o[7], o[8]);
	
	Vec3 p = obb.origin - ray.origin;
	
	Vec3 f(
		X.Dot(ray.direction),
		Y.Dot(ray.direction),
		Z.Dot(ray.direction)
	);
	
	Vec3 e(X.Dot(p), Y.Dot(p), Z.Dot(p));
	
	float t[6] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 3; ++i) {
		if (f[i] == 0.0f) {
			if (-e[i] - size[i]>0 || -e[i] + size[i]<0) {
				return -1;
			}
			f[i] = 0.00001f; 
		}
		t[i * 2 + 0] = (e[i] + size[i]) / f[i]; 
		t[i * 2 + 1] = (e[i] - size[i]) / f[i]; 
	}

	float tmin = fmaxf(
		fmaxf(
			fminf(t[0], t[1]),
			fminf(t[2], t[3])),
		fminf(t[4], t[5])
	);
	float tmax = fminf(
		fminf(
			fmaxf(t[0], t[1]),
			fmaxf(t[2], t[3])),
		fmaxf(t[4], t[5])
	);
	
	if (tmax< 0) {
		return -1.0f;
	}
	
	if (tmin>tmax) {
		return -1.0f;
	}
	
	if (tmin< 0.0f) {
		return tmax;
	}
	return tmin;
}


float RayCast(const Plane & plane, const Ray & ray)
{
	float nd = ray.direction.Dot(plane.normal);
	float pn = ray.origin.Dot(plane.normal);

	if (nd >= 0.0f)
	{
		return -1.0f;
	}

	float t = (plane.distance - pn) / nd;
	if (t >= 0.0f)
	{
		return t;
	}

	return -1.0f;
}

bool Linetest(const Sphere & sphere, const Line & line)
{
	Point3D closestPoint = ClosestPointOnLine(sphere.center, line);
	float distanceSq = (sphere.center - closestPoint).MagnitudeSq();
	return distanceSq <= sphere.radius * sphere.radius;
}

bool Linetest(const OBB & obb, const Line & line)
{
	Ray ray;
	ray.origin = line.start;
	ray.direction = (line.end - line.start).GetNormalized();
	float t = RayCast(obb, ray);
	return t >= 0.0f && t <= (line.end - line.start).MagnitudeSq();
}

bool Linetest(const AABB & aabb, const Line & line)
{
	Ray ray;
	ray.origin = line.start;
	ray.direction = (line.end - line.start).GetNormalized();
	float t = RayCast(aabb, ray);
	return t >= 0.0f && t <= (line.end - line.start).MagnitudeSq();
}

bool Linetest(const Plane & plane, const Line & line)
{
	Vec3 ab = line.end - line.start;
	float na = plane.normal.Dot(ab);
	float nab = plane.normal.Dot(ab);
	
	float t = (plane.distance - na) / nab;

	return t >= 0.0f && t <= 1.0f;
}

bool PointInTriangle(const Point3D & point, const Triangle & triangle)
{
	Vec3 a = triangle.a - point;
	Vec3 b = triangle.b - point;
	Vec3 c = triangle.c - point;

	Vec3 normalPBC = b.Cross(c);
	Vec3 normalPCA = c.Cross(a);
	Vec3 normalPAB = a.Cross(b);

	if (normalPBC.Dot(normalPCA) < 0.0f)
	{
		return false;
	}
	else if (normalPBC.Dot(normalPAB) < 0.0f)
	{
		return false;
	}

	return true;
}

Plane FromTriangle(const Triangle & triangle)
{
	Plane plane;
	plane.normal = (triangle.b - triangle.a).Cross(triangle.c - triangle.a).GetNormalized();
	plane.distance = plane.normal.Dot(triangle.a);
	return plane;
}

Point3D ClosestPointInTriangle(const Triangle & triangle, const Point3D & point)
{
	Plane plane = FromTriangle(triangle);
	if (PointInTriangle(point, triangle))
	{
		return point;
	}

	Point3D c1 = ClosestPointOnLine(point, Line(triangle.a, triangle.b));
	Point3D c2 = ClosestPointOnLine(point, Line(triangle.b, triangle.c));
	Point3D c3 = ClosestPointOnLine(point, Line(triangle.c, triangle.a));

	float magsq1 = (point - c1).Magnitude();
	float magsq2 = (point - c2).Magnitude();
	float magsq3 = (point - c3).Magnitude();

	if (magsq1 < magsq2 && magsq1 < magsq3)
	{
		return c1;
	}
	else if (magsq2 < magsq1 && magsq2 < magsq3)
	{
		return c2;
	}

	return c3;
}

bool TriangleShpere(const Triangle & triangle, const Sphere & sphere)
{
	Point3D closest = ClosestPointInTriangle(triangle, sphere.center);
	float magSq = (closest - sphere.center).MagnitudeSq();
	return magSq <= sphere.radius * sphere.radius;
}
