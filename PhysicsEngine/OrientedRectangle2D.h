#pragma once

#include "Vec2.h"

class OrientedRectangle2D
{
public:
	Point2D origin;
	Vec2 halfExtents;
	float rotation;

public:
	OrientedRectangle2D();
	OrientedRectangle2D(const Point2D& _origin, const Vec2& _halfExtents, float _rotation);
	
};

