#pragma once
#include "Vec2.h"

class Circle2D
{
public:
	Point2D center;
	float radius;

public:
	Circle2D();
	Circle2D(const Point2D& _center, float _radius);
};