#pragma once

#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "AABB.h"
#include "OBB.h"
#include "Triangle.h"
#include "RaycastResult.h"


bool Raycast(const Sphere& sphere, const Ray& ray, RaycastResult& result);
bool Raycast(const Plane& plane, const Ray& ray, RaycastResult& result);
bool Raycast(const AABB& aabb, const Ray& ray, RaycastResult& result);
bool Raycast(const OBB& obb, const Ray& ray, RaycastResult& result);
bool Raycast(const Triangle& triangle, const Ray& ray, RaycastResult& result);
