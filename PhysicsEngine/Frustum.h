#pragma once
#include "Plane.h"
#include "Sphere.h"
#include "Vec3.h"

class Frustum {
public:
	union {
		struct {
			Plane top;
			Plane bottom;
			Plane left;
			Plane right;
			Plane _near;
			Plane _far;
		};
		Plane planes[6];
	};

	Frustum() { }
	~Frustum() {}
};

bool Intersects(const Frustum& f, const Point3D& p);
bool Intersects(const Frustum& f, const Sphere& s);
