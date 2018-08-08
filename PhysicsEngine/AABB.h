#pragma once
#include "Vec3.h"

class AABB
{
public:
	Point3D origin;
	Vec3 size;

public:
	Vec3 GetMin() const;
	Vec3 GetMax() const;
	static AABB FromMinMax(const Vec3& _min, const Vec3& _max);

public:
	AABB();
	AABB(const Point3D& _origin, const Vec3& _size);
	~AABB();
};

